<?php
/**
 * @file
 * Administer module alttracker.module.
 */
 
function alttracker_admin_settings($form, &$form_state) {
  $form['alttracker_taxonomy'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display taxonomy'),
    '#default_value' => variable_get('alttracker_taxonomy'),
  );

  $options = node_type_get_names();
  print_r($options);
  $form['alttracker_node_type'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display taxonomy'),
    '#default_value' => variable_get('alttracker_taxonomy'),
  );


  return system_settings_form($form);
}
