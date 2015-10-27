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
  return system_settings_form($form);
}
