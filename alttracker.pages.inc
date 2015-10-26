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
    ->fetchAllAssoc('nid');
    
    print_r($nids);

    $nodes = node_load_multiple($nids);
    $page = node_view_multiple($nodes);
    
/*  $rows = array();
  if (!empty($nodes)) {
    // Now, get the data and put into the placeholder array.
    $result = db_query('SELECT n.nid, n.title, n.type, n.changed, n.uid, u.name, l.comment_count FROM {node} n INNER JOIN {node_comment_statistics} l ON n.nid = l.nid INNER JOIN {users} u ON n.uid = u.uid WHERE n.nid IN (:nids)', array(':nids' => array_keys($nodes)), array('target' => 'slave'));
    foreach ($result as $node) {
      $node->last_activity = $nodes[$node->nid]->changed;
      $nodes[$node->nid] = $node;
    }

    // Display the data.
    foreach ($nodes as $node) {
      // Determine the number of comments.
      $comments = 0;
      if ($node->comment_count) {
        $comments = $node->comment_count;

        if ($new = comment_num_new($node->nid)) {
          $comments .= '<br />';
          $comments .= l(format_plural($new, '1 new', '@count new'), 'node/' . $node->nid, array('fragment' => 'new'));
        }
      }

      $row = array(
        'type' => check_plain(node_type_get_name($node->type)),
        'title' => array('data' => l($node->title, 'node/' . $node->nid) . ' ' . theme('mark', array('type' => node_mark($node->nid, $node->changed)))),
        'author' => array('data' => theme('username', array('account' => $node))),
        'replies' => array('class' => array('replies'), 'data' => $comments),
        'last updated' => array('data' => t('!time ago', array('!time' => format_interval(REQUEST_TIME - $node->last_activity)))),
      );

      $rows[] = $row;
    }
  }
*/
  $page['first-pager'] = array(
    '#theme' => 'altpager',
    '#weight' => -10,
  );
/*
  $page['alttracker'] = array(
    '#rows' => $rows,
    '#header' => array(t('Type'), t('Title'), t('Author'), t('Replies'), t('Last updated')),
    '#theme' => 'table',
    '#empty' => t('No content available.'),
    '#attached' => array(
      'css' => array(drupal_get_path('module', 'alttracker') . '/tracker.css' => array()),
    ),
    '#weight' => 0,
  );
*/
  $page['last-pager'] = array(
    '#theme' => 'altpager',
    '#weight' => 10,
  );
  $page['#sorted'] = TRUE;

  return $page;
}
