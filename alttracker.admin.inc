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
    '#description' => t('Select taxonomy terms to ignore in tracker outout.')
  );
  $vocabularies = taxonomy_vocabulary_get_names();
  print_r($vocabularies);
  
  foreach($vocabularies as $vocabulary){
    $form['alttracker_vocabulary']['alttracker_vocabulary_' . $vocabulary->vid] = array(
      '#type' => 'textfield',
      '#title' => $vocabulary->name,
      '#autocomplete_path' => 'alttracker/autocomplete/' . $vocabulary->vid, 
      '#default_value' => variable_get('alttracker_vocabulary_' . $vocabulary->vid), 
    );
  }

  return system_settings_form($form);
}

function alttracker_autocomplete_callback($vid, $str){
  $matches = array();
  echo $vid;
  echo $str;
  $result = db_select('taxonomy_term_data', 't')
    -> fields('t', array('tid', 'name'))
    -> condition('vid', $vid, '=')
    -> condition('name', $str.'%%', 'LIKE')
    -> range(0, 10)
    -> execute();
  foreach ($result as $term) {
    $matches[$term->tid] = check_plain($term->name);
  }
  drupal_json_output($matches);
}