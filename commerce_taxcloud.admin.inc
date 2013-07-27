<?php

/**
 * Generates administrative form.
 */
function commerce_taxcloud_admin_form() {
  $form = array();

  $form['commerce_taxcloud_api_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Taxcloud API ID'),
    '#default_value' => variable_get('commerce_taxcloud_api_id', ''),
    '#size' => 60,
    '#maxlength' => 255,
    '#required' => TRUE,
  );
  $form['commerce_taxcloud_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Taxcloud API Key'),
    '#default_value' => variable_get('commerce_taxcloud_api_key', ''),
    '#size' => 60,
    '#maxlength' => 255,
    '#required' => TRUE,
  );
  $form['commerce_taxcloud_usps_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Your USPS ID'),
    '#description' => t('If you would like to use USPS verification please enter your USPS ID here. Instructions on obtaining this are available at: https://taxcloud.net/account/api/ under the VerifyAddress tab'),
    '#default_value' => variable_get('commerce_taxcloud_usps_id', ''),
    '#size' => 60,
    '#maxlength' => 255,
  );
  $form['commerce_taxcloud_tic_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Default TIC (Taxability Information Code)'),
    '#description' => t('You can find this at https://taxcloud.net/account/tics/'),
    '#default_value' => variable_get('commerce_taxcloud_tic_id', '00000'),
    '#size' => 60,
    '#maxlength' => 255,
    '#required' => TRUE,
  );

  $form['commerce_taxcloud_store'] = array(
    '#type' => 'fieldset',
    '#title' => t('Store Address'),
    '#collapsed' => FALSE,
    '#collapsible' => TRUE,
  );
  $form['commerce_taxcloud_store']['commerce_taxcloud_address1'] = array(
    '#type' => 'textfield',
    '#title' => t('Address 1'),
    '#default_value' => variable_get('commerce_taxcloud_address1', ''),
    '#size' => 60,
    '#maxlength' => 255,
    '#required' => TRUE,
  );
  $form['commerce_taxcloud_store']['commerce_taxcloud_address2'] = array(
    '#type' => 'textfield',
    '#title' => t('Address 2'),
    '#default_value' => variable_get('commerce_taxcloud_address2', ''),
    '#size' => 60,
    '#maxlength' => 255,
  );
  $form['commerce_taxcloud_store']['commerce_taxcloud_city'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#default_value' => variable_get('commerce_taxcloud_city', ''),
    '#size' => 60,
    '#maxlength' => 255,
    '#required' => TRUE,
  );
  $form['commerce_taxcloud_store']['commerce_taxcloud_state'] = array(
    '#type' => 'textfield',
    '#title' => t('State'),
    '#description' => t('The two letter abbreivation for your state, e.g. OK, NY, etc.'),
    '#default_value' => variable_get('commerce_taxcloud_state', ''),
    '#size' => 5,
    '#maxlength' => 2,
    '#required' => TRUE,
  );
  $form['commerce_taxcloud_store']['commerce_taxcloud_zip'] = array(
    '#type' => 'textfield',
    '#title' => t('Zip'),
    '#description' => t('Full 9 digit zip code separated by a hyphen provided by TaxCloud, e.g. 12345-6789.'),
    '#default_value' => variable_get('commerce_taxcloud_zip', ''),
    '#size' => 12,
    '#maxlength' => 10,
    '#required' => TRUE,
  );

  $form['commerce_taxcloud_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable?'),
    '#default_value' => variable_get('commerce_taxcloud_enable', 0),
    '#states' => array(
      'enabled' => array(
        ':input[name="commerce_taxcloud_api_id"]' => array('filled' => TRUE),
        ':input[name="commerce_taxcloud_api_key"]' => array('filled' => TRUE),
        ':input[name="commerce_taxcloud_address1"]' => array('filled' => TRUE),
        ':input[name="commerce_taxcloud_city"]' => array('filled' => TRUE),
        ':input[name="commerce_taxcloud_state"]' => array('filled' => TRUE),
        ':input[name="commerce_taxcloud_zip"]' => array('filled' => TRUE),
      ),
    ),
  );

  return system_settings_form($form);
}