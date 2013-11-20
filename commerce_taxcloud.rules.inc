<?php

/**
 * @file
 * Rules integration for Commerce TaxCloud.
 */

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

  $actions['commerce_taxcloud_action_return'] = array(
    'label' => t('Refund sales tax on returned items.'),
    'parameter' => array(
      'commerce_line_items' => array(
        'type' => 'list<commerce_line_item>',
        'label' => 'Commerce Line Items',
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
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  commerce_taxcloud_authorize_with_capture($order_wrapper);
}

/**
 * Inform Tax Cloud that we have successfully authorized and captured the
 * payment for the taxes.
 */
function commerce_taxcloud_action_authorize_capture($order) {
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  commerce_taxcloud_authorize_with_capture($order_wrapper);
}

/**
 * Process a list of returned Commerce Line Items.
 */
function commerce_taxcloud_action_return($line_items) {
  foreach ($line_items as $line_item) {
    $line_item = entity_metadata_wrapper('commerce_line_item', $line_item);
  }
  commerce_taxcloud_returned($line_items);
}
