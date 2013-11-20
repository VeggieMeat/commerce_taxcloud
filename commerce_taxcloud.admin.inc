<?php

/**
 * @file
 * Contains forms and form handlers for Commerce TaxCloud.
 */

/**
 * Generates administrative form.
 */
function commerce_taxcloud_admin_form($form, &$form_state) {
  $field_name = 'commerce_taxcloud_tic';
  $field = field_info_field($field_name);

  $form['commerce_taxcloud_api_id'] = array(
    '#type' => 'textfield',
    '#title' => t('TaxCloud API ID'),
    '#description' => t('This information can be found in the TaxCloud <a href="@link">Websites</a> section.', array('@link' => 'https://taxcloud.net/account/websites/')),
    '#default_value' => variable_get('commerce_taxcloud_api_id', ''),
    '#size' => 60,
    '#maxlength' => 255,
    '#required' => TRUE,
  );
  $form['commerce_taxcloud_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('TaxCloud API Key'),
    '#default_value' => variable_get('commerce_taxcloud_api_key', ''),
    '#size' => 60,
    '#maxlength' => 255,
    '#required' => TRUE,
  );
  $form['commerce_taxcloud_usps_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Your USPS ID'),
    '#description' => t('If you would like to use USPS verification please enter your USPS ID here. Instructions on obtaining this are available at <a href="@link">TaxCloud</a> under the VerifyAddress tab.', array('@link' => 'https://taxcloud.net/account/api/')),
    '#default_value' => variable_get('commerce_taxcloud_usps_id', ''),
    '#size' => 60,
    '#maxlength' => 255,
  );

  $form['commerce_taxcloud_store'] = array(
    '#type' => 'fieldset',
    '#title' => t('Store Address'),
    '#collapsed' => FALSE,
    '#collapsible' => TRUE,
    '#tree' => TRUE,
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
    '#description' => t('The two letter abbreviation for your state, for example, OK, NY, etc.'),
    '#default_value' => variable_get('commerce_taxcloud_state', ''),
    '#size' => 5,
    '#maxlength' => 2,
    '#required' => TRUE,
  );
  $form['commerce_taxcloud_store']['commerce_taxcloud_zip'] = array(
    '#type' => 'textfield',
    '#title' => t('Zip'),
    '#description' => t('Full 9 digit zip code separated by a hyphen provided by TaxCloud, for example, 12345-6789.'),
    '#default_value' => variable_get('commerce_taxcloud_zip', ''),
    '#size' => 12,
    '#maxlength' => 10,
    '#required' => TRUE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
  );

  return $form;
}

/**
 * Submit handler for commerce_taxcloud_admin_form.
 */
function commerce_taxcloud_admin_form_submit($form, &$form_state) {
  variable_set('commerce_taxcloud_api_id', $form_state['values']['commerce_taxcloud_api_id']);
  variable_set('commerce_taxcloud_api_key', $form_state['values']['commerce_taxcloud_api_key']);
  variable_set('commerce_taxcloud_usps_id', $form_state['values']['commerce_taxcloud_usps_id']);
  variable_set('commerce_taxcloud_address1', $form_state['values']['commerce_taxcloud_store']['commerce_taxcloud_address1']);
  variable_set('commerce_taxcloud_address2', $form_state['values']['commerce_taxcloud_store']['commerce_taxcloud_address2']);
  variable_set('commerce_taxcloud_city', $form_state['values']['commerce_taxcloud_store']['commerce_taxcloud_city']);
  variable_set('commerce_taxcloud_state', $form_state['values']['commerce_taxcloud_store']['commerce_taxcloud_state']);
  variable_set('commerce_taxcloud_zip', $form_state['values']['commerce_taxcloud_store']['commerce_taxcloud_zip']);
}

/**
 * Form to assign Taxability Information Codes to line items types.
 */
function commerce_taxcloud_admin_line_item_form($form, &$form_state) {
  $field_name = 'commerce_taxcloud_tic';
  $field = field_info_field($field_name);

  $form['#tree'] = TRUE;

  foreach (commerce_line_item_types() as $type => $line_item_type) {
    $instance[$type] = field_info_instance('commerce_line_item', 'commerce_taxcloud_tic', $type);
    $enabled[$type] = (!empty($instance[$type]));

    $form['line_item_types'][$type] = array(
      '#type' => 'fieldset',
      '#title' => t('@name (@machine_name)', array('@name' => $line_item_type['name'], '@machine_name' => $type)),
    );

    $form['line_item_types'][$type]['enabled'] = array(
      '#type' => 'checkbox',
      '#default_value' => $enabled[$type],
      '#title' => t('Enabled'),
    );

    $form['line_item_types'][$type]['default_tic'] = array(
      '#type' => 'select',
      '#title' => t('Taxability Information Code'),
      '#description' => t('Default TIC for this line item type.'),
      '#options' => commerce_taxcloud_tic_options(),
      '#default_value' => commerce_taxcloud_tic_options_default($type),
    );
  }

  if (!empty($form_state['commerce_taxcloud']['delete_instances'])) {
    $type_plural = format_plural(count($form_state['commerce_taxcloud']['delete_instances']), 'type', 'types');
    $affirmation = t('I understand that TaxCloud will be permanently removed from the line item @type_plural %line_item_types.',
      array(
        '@type_plural' => $type_plural,
        '%line_item_types' => implode(', ', $form_state['commerce_taxcloud']['delete_instances']),
      )
    );
  }

  $form['confirmation'] = array(
    '#type' => 'checkbox',
    '#title' => !empty($affirmation) ? $affirmation : '',
    '#default_value' => FALSE,
    '#access' => FALSE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
  );

  if (!empty($form_state['commerce_taxcloud']['delete_instances'])) {
    $form['confirmation']['#access'] = TRUE;
    drupal_set_message(t('You must click the confirmation checkbox to confirm that you want to delete TaxCloud data.'), 'warning');
  }

  return $form;
}

/**
 * Submit handler for commerce_taxcloud_admin_line_item_form.
 */
function commerce_taxcloud_admin_line_item_form_submit($form, &$form_state) {
  $form_state['commerce_taxcloud']['delete_instances'] = array();
  foreach ($form_state['values']['line_item_types'] as $type => $values) {
    $instance = field_info_instance('commerce_line_item', 'commerce_taxcloud_tic', $type);

    if ($values['enabled'] && !$instance) {
      commerce_taxcloud_configure_line_item_type($type, $values['default_tic']);
      commerce_taxcloud_tic_init($type, $values['default_tic']);
      drupal_set_message(t('TaxCloud has been enabled on the %type line item type with a default Taxability Information Code of %tic.', array('%type' => $type, '%tic' => $values['default_tic'])));
    }

    elseif ($instance && !$values['enabled']) {
      if (empty($form_state['values']['confirmation'])) {
        $form_state['commerce_taxcloud']['delete_instances'][] = $type;
        $form_state['rebuild'] = TRUE;
      }
      else {
        field_delete_instance($instance);
        drupal_set_message(t('TaxCloud has been disabled on the %type line item type.', array('%type' => $type)));
      }
    }
  }
}
