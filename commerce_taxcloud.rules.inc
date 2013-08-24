<?php


/**
 * Implements hook_rules_action_info().
 */
function commerce_taxcloud_rules_action_info() {
  $actions = array();

  $actions['commerce_taxcloud_action_apply_taxes'] = array(
    'label' => t('Retrieve and Set taxes from Tax Cloud.'),
    'parameter' => array(
      'commerce_line_item' => array(
        'type' => 'commerce_line_item',
        'label' => t('Line item'),
      ),
      'tax_rate_name' => array(
        'type' => 'text',
        'label' => t('Tax rate'),
        'options list' => 'commerce_tax_rate_titles',
      ),
    ),
    'group' => t('Commerce Tax Cloud'),
    /*
    'callbacks' => array(
      'execute' => 'commerce_taxcloud_set_taxes',
    ),
    */
  );
  $actions['commerce_taxcloud_action_authorize_capture'] = array(
    'label' => t('Inform Tax Cloud that we have successfully authorized and captured the payment for the taxes.'),
    'parameter' => array(
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Order'),
      ),
    ),
    'group' => t('Commerce Tax Cloud'),
  );

  return $actions;
}

/**
 * @todo fill this in.
 */
function commerce_taxcloud_action_apply_taxes($line_item, $tax_rate_name) {
  if (strpos($_SERVER['REQUEST_URI'], 'checkout')) {
    if ($tax_rate = commerce_tax_rate_load($tax_rate_name)) {
      $wrapper = entity_metadata_wrapper('commerce_line_item', $line_item);
      if ($tax_price = $tax_rate['calculation_callback']($tax_rate, $wrapper)) {
        // Add the tax to the unit price's data array along with a display inclusive
        // property used to track whether or not the tax is included in the price.
        $included = FALSE;

        // Retrieve the order.
        $order = commerce_order_load($wrapper->order_id->value());

        // Retrieve the billing profile and set the destination address for
        // Tax Cloud.
        $billing = commerce_customer_profile_load($order->commerce_customer_billing[LANGUAGE_NONE][0]['profile_id']);
        $customer_address = $billing->commerce_customer_address[LANGUAGE_NONE][0];

        // Retrive the line items for the order.
        $products = array(
          array(
            'productid' => $line_item->data['context']['product_ids'][0],
            'price' => $line_item->commerce_unit_price[LANGUAGE_NONE][0]['amount'] / 100,
            'qty' => 1,
            'cart_item_index' => $line_item->line_item_id,
          ),
        );

        $cartid = $line_item->order_id;
        $taxes = commerce_taxcloud_communication($customer_address, $products, $cartid);
        $tax_price['amount'] = $taxes[$line_item->line_item_id] * 100;
        // If the rate specifies a valid tax type that is display inclusive...
        if (($tax_type = commerce_tax_type_load($tax_rate['type'])) &&
          $tax_type['display_inclusive']) {
          // Include the tax amount in the displayed unit price.
          $wrapper->commerce_unit_price->amount = $wrapper->commerce_unit_price->amount->value() + $tax_price['amount'];
          $included = TRUE;
        }

        // Update the data array with the tax component.
        $wrapper->commerce_unit_price->data = commerce_price_component_add(
          $wrapper->commerce_unit_price->value(),
          $tax_rate['price_component'],
          $tax_price,
          $included
        );
      }
    }
  }
}

/**
 * @todo fill this in.
 */
function commerce_taxcloud_action_authorize_capture($order) {
  // Retrieve the billing profile and set the destination address for
  // Tax Cloud.
  $billing = commerce_customer_profile_load($order->commerce_customer_billing[LANGUAGE_NONE][0]['profile_id']);
  $customer_address = $billing->commerce_customer_address[LANGUAGE_NONE][0];

  foreach ($order->commerce_line_items['und'] as $li) {
    $item = commerce_line_item_load($li['line_item_id']);
    if ($item->type == 'product') {

      $product = array();

      $product['productid'] = $item->data['context']['product_ids'][0];
      $product['price'] = $item->commerce_unit_price[LANGUAGE_NONE][0]['amount'] / 100;
      $product['qty'] = $item->quantity;
      $product['cart_item_index'] = $item->line_item_id;

      $products[] = $product;
    }
  }

  $cartid = $order->order_id;
  commerce_taxcloud_communication($customer_address, $products, $cartid);

  // Authorized
  commerce_taxcloud_authorized_captured($cartid, $products, $order->order_id);
}
