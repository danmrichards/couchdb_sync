<?php

/**
 * @file
 * CouchDB Sync's implementation of its own API.
 */

/**
 * Implements hook_couchdb_sync_flatteners().
 */
function couchdb_sync_couchdb_sync_flatteners() {
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
    'FileFlattener' => array(
      'name' => '"File" CouchDB Sync Flattener plugin',
      'description' => 'Provides a CouchDB sync flattener for "file" fields.',
      'handler' => array(
        'class' => 'FileFlattener',
        'file' => 'FileFlattener.inc',
        'path' => drupal_get_path('module', 'couchdb_sync') . '/plugins',
      ),
    ),
    'ListFloatFlattener' => array(
      'name' => '"List (float)" CouchDB Sync Flattener plugin',
      'description' => 'Provides a CouchDB sync flattener for "list_float" fields.',
      'handler' => array(
        'class' => 'ListFloatFlattener',
        'file' => 'ListFloatFlattener.inc',
        'path' => drupal_get_path('module', 'couchdb_sync') . '/plugins',
      ),
    ),
    'ListIntegerFlattener' => array(
      'name' => '"List (integer)" CouchDB Sync Flattener plugin',
      'description' => 'Provides a CouchDB sync flattener for "list_integer" fields.',
      'handler' => array(
        'class' => 'ListIntegerFlattener',
        'file' => 'ListIntegerFlattener.inc',
        'path' => drupal_get_path('module', 'couchdb_sync') . '/plugins',
      ),
    ),
  );
}

/**
 * Implements hook_couchdb_sync_processors().
 */
function couchdb_sync_couchdb_sync_processors() {
  return array(
    'QueueProcessor' => array(
      'name' => 'Queue',
      'description' => 'Processes entities into a queue. Each queue item is then pushed to CouchDB one-by-one.',
      'handler' => array(
        'class' => 'QueueProcessor',
        'file' => 'QueueProcessor.inc',
        'path' => drupal_get_path('module', 'couchdb_sync') . '/plugins',
      ),
    ),
    // TODO: Add new processor plugin to sync entities immediately.
  );
}
