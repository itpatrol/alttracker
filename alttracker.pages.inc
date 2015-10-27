<?php

/**
 * @file
 * User page callbacks for tracker.module.
 */


/**
 * Page callback: prints a listing of active nodes on the site.
 *
 * Queries the database for info, adds RDFa info if applicable, and generates
 * the render array that will be used to render the page.
 */
function alttracker_page($account = NULL, $set_title = FALSE) {
  if ($account) {
    $query = db_select('alttracker_user', 't')->extend('AltPager');
    $query->condition('t.uid', $account->uid);

    if ($set_title) {
      // When viewed from user/%user/track, display the name of the user
      // as page title -- the tab title remains Track so this needs to be done
      // here and not in the menu definition.
      drupal_set_title(format_username($account));
    }
  }
  else {
    $query = db_select('alttracker_node', 't', array('target' => 'slave'))->extend('AltPager');
  }

  // This array acts as a placeholder for the data selected later
  // while keeping the correct order.
  $nids = $query
    ->addTag('node_access')
    ->fields('t', array('nid', 'changed'))
    ->condition('t.published', 1)
    ->orderBy('t.changed', 'DESC')
    ->execute()
    ->fetchCol();

  $page['first-pager'] = array(
    '#theme' => 'altpager',
    '#weight' => -10,
  );
    
  $nodes = node_load_multiple($nids);
  foreach($nodes as $node){
    $page['nodes'][] = array(
      '#theme' => 'alttracker_node',
      '#variables' => array('node' => $node),
    );
  }

  $page['last-pager'] = array(
    '#theme' => 'altpager',
    '#weight' => 10,
  );
  $page['#sorted'] = TRUE;

  return $page;
}
