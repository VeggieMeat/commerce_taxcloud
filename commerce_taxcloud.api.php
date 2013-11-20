<?php

/**
 * @file
 * This file contains no working PHP code; it exists to provide additional
 * documentation for doxygen as well as to document hooks in the standard
 * Drupal manner.
 */

/**
 * Provide your own Rules actions that integrate with TaxCloud.
 *
 * TaxCloud requires that sales tax is collected through them. They will not
 * allow you to use the service only for lookups. However, if you are in a
 * unique situation where the actions provided by the module for authorization
 * and capture will not suffice, this hook allows you to inform the Commerce
 * TaxCloud module that you do in fact meet the requirements of communicating
 * with TaxCloud.
 *
 * @param array $actions
 *   A list of action machine names that capture TaxCloud transactions.
 */
function hook_commerce_taxcloud_actions_alter(&$actions) {
  $actions[] = 'my_custom_processing_action';
}

/**
 * Alter Commerce TaxCloud destination address.
 *
 * If you are splitting an order between multiple destinations, or if you need
 * to perform address verification through another module, this hook will allow
 * you to override the destination address per line item. Remember, you always
 * need your ZIP code to be ZIP+4.
 *
 * @param \TaxCloud\Address $destination
 *   The destination for the item.
 * @param array $context
 *   - line_item_wrapper: A clone of the current Line Item entity metadata
 *   wrapper.
 */
function hook_commerce_taxcloud_destination_alter(&$destination, $context) {
  $destination->setZip5('12345');
  $destination->setZip4('6789');
}

/**
 * Alter Commerce TaxCloud origin address.
 *
 * If you are shipping an order from multiple destinations, this hook will
 * allow you to override the origin address per line item.
 *
 * @param \TaxCloud\Address $origin
 *   The destination for the item.
 * @param array $context
 *   - line_item_wrapper: A clone of the current Line Item entity metadata
 *   wrapper.
 */
function hook_commerce_taxcloud_origin_alter(&$origin, $context) {
  $origin->setAddress1('123 E Main St.');
  $origin->setCity('Smallville');
  $origin->setState('WA');
  $origin->setZip5('12345');
  $origin->setZip4('6789');
}
