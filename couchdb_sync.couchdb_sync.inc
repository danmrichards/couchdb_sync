<?php

/**
 * @file
 * CouchDB Sync's implementation of its own API.
 */

/**
 * Implements hook_couchdb_sync_flatteners().
 */
function couchdb_sync_couchdb_sync_flatteners() {
  // TODO: Add handler plugins for all core field types (if required).
  return array(
    'GenericFlattener' => array(
      'name' => 'Generic CouchDB Sync Flattener plugin',
      'description' => 'Provides a generic CouchDB sync flattener for use with fields that do not have a defined plugin.',
      'handler' => array(
        'class' => 'GenericFlattener',
        'file' => 'GenericFlattener.inc',
        'path' => drupal_get_path('module', 'couchdb_sync') . '/plugins',
      ),
    ),
    'TextWithSummaryFlattener' => array(
      'name' => '"Text with Summary" CouchDB Sync Flattener plugin',
      'description' => 'Provides a CouchDB sync flattener for "text_with_summary" fields.',
      'handler' => array(
        'class' => 'TextWithSummaryFlattener',
        'file' => 'TextWithSummaryFlattener.inc',
        'path' => drupal_get_path('module', 'couchdb_sync') . '/plugins',
      ),
    ),
    'ImageFlattener' => array(
      'name' => '"Image" CouchDB Sync Flattener plugin',
      'description' => 'Provides a CouchDB sync flattener for "image" fields.',
      'handler' => array(
        'class' => 'ImageFlattener',
        'file' => 'ImageFlattener.inc',
        'path' => drupal_get_path('module', 'couchdb_sync') . '/plugins',
      ),
    ),
    'ListTextFlattener' => array(
      'name' => '"List (text)" CouchDB Sync Flattener plugin',
      'description' => 'Provides a CouchDB sync flattener for "list_text" fields.',
      'handler' => array(
        'class' => 'ListTextFlattener',
        'file' => 'ListTextFlattener.inc',
        'path' => drupal_get_path('module', 'couchdb_sync') . '/plugins',
      ),
    ),
  );
}
