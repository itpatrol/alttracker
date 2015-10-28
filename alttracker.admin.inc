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
  $form['alttracker_node_type'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Display selected node types'),
    '#description' => t('If none selected, will display all types'),
    '#default_value' => variable_get('alttracker_node_type'),
    '#options' => $options,
  );

  $form['alttracker_vocabulary'] = array(
    '#type' => 'fieldset',
    '#title' => t('Ignore terms'),
  );
  $vocabularies = taxonomy_vocabulary_get_names();
  print_r($vocabularies);

  return system_settings_form($form);
}
