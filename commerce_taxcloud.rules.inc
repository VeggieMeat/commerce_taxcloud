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
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  commerce_taxcloud_authorize_with_capture($order_wrapper);
}
