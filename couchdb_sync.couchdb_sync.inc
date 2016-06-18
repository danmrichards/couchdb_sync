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
    'CouchDBSyncGenericFlattener' => array(
      'name' => 'Generic CouchDB Sync Flattener plugin',
      'description' => 'Provides a generic CouchDB sync flattener for use with fields that do not have a defined plugin.',
      'handler' => array(
        'class' => 'CouchDBSyncGenericFlattener',
        'file' => 'CouchDBSyncGenericFlattener.inc',
        'path' => drupal_get_path('module', 'couchdb_sync') . '/plugins',
      ),
    ),
  );
}
