<?php


/**
 * Implements hook_rules_action_info().
 */
function commerce_taxcloud_rules_action_info() {
  $actions = array();

  $actions['commerce_taxcloud_action_authorize'] = array(
    'label' => t('Authorize sales tax.'),
    'parameter' => array(
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Order'),
      ),
    ),
    'group' => t('Commerce TaxCloud'),
  );

  $actions['commerce_taxcloud_action_capture'] = array(
    'label' => t('Capture sales tax.'),
    'parameter' => array(
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Order'),
      ),
    ),
    'group' => t('Commerce TaxCloud'),
  );

  $actions['commerce_taxcloud_action_authorize_capture'] = array(
    'label' => t('Authorize and capture sales tax.'),
    'parameter' => array(
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Order'),
      ),
    ),
    'group' => t('Commerce TaxCloud'),
  );

  return $actions;
}

/**
 * Inform TaxCloud that we have successfully authorized the payment for the
 * taxes.
 */
function commerce_taxcloud_action_authorize($order) {
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  commerce_taxcloud_authorize_with_capture($order_wrapper);
}

/**
 * Inform TaxCloud that we have successfully captured the payment for the
 * taxes.
 */
function commerce_taxcloud_action_capture($order) {
  commerce_taxcloud_authorize_with_capture($order->order_id);
}

/**
 * Inform Tax Cloud that we have successfully authorized and captured the
 * payment for the taxes.
 */
function commerce_taxcloud_action_authorize_capture($order) {
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  commerce_taxcloud_authorize_with_capture($order_wrapper);
}
