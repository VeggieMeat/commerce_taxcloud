<?php


/**
 * Implements hook_rules_action_info().
 */
function commerce_taxcloud_rules_action_info() {
  $actions = array();

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
