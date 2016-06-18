<?php

/**
 * @file
 * API documentation for the CouchDB Sync module.
 */

/**
 * CouchDB Sync export provides a CTools based plugin API.
 *
 * There is 1 type of plugin that can be defined: Flattener.
 *
 * @see CouchDBSyncFlattenerInterface
 *
 * @defgroup pluginapi Plugin API
 *
 * @{
 */

/**
 * Example of a CTools plugin hook.
 *
 * All modules defining plugins must also implement this hook. This enables the
 * module to then implement the plugin hook: hook_couchdb_sync_flatteners.
 *
 * @see hook_couchdb_sync_flatteners()
 */
function hook_ctools_plugin_api($owner, $api) {
  if ($owner == 'couchdb_sync' && $api == 'plugins') {
    return array('version' => 1);
  }
}

/**
 * Defines a CouchDB Sync flattener plugin.
 *
 * All plugins defined by this hook will be tested to ensure that their class
 * implements the CouchDBSyncFlattenerInterface interface. The 'path' attribute
 * is optional, if omitted the root directory of the module will be checked. The
 * module implementing this hook must also implement hook_ctools_plugin_api.
 *
 * @see CouchDBSyncFlattenerInterface
 * @see hook_ctools_plugin_api()
 */
function hook_couchdb_sync_flatteners() {
  return array(
    'MyAwesomeFieldFlattener' => array(
      'name' => 'My Awesome FieldFlattener',
      'description' => 'Provides a flattener for my awesome field',
      'handler' => array(
        'class' => 'MyAwesomeFieldFlattener',
        'file' => 'MyAwesomeFieldFlattener.inc',
        'path' => drupal_get_path('module', 'my_awesome_module') . '/plugins',
      ),
    ),
  );
}

/**
 * @}
 */

/**
 * @defgroup couchdb_sync_hooks CouchDB Sync Hooks
 *
 * @{
 */

/**
 * Alters the list of fields present on a flattened entity.
 *
 * This occurs before the sync to CouchDB and allows additional data to be
 * pulled from entities. For example data stored in entity properties.
 *
 * @param array $entity_fields
 *   Array of entity fields as defined by field_info_instances().
 * @param string $type
 *   The type of entity being flattened.
 * @param object $entity
 *   The raw Drupal entity being flattened.
 *
 * @see field_info_instances()
 */
function hook_couchdb_sync_flatten_entity_fields_alter(array &$entity_fields, $type, $entity) {
  switch ($type) {
    // Add the SKU field for commerce products.
    case 'commerce_product':
      $entity_fields[] = 'sku';
      break;
  }
}

/**
 * Act on a flattened entity before it is inserted into CouchDB.
 *
 * This hook only runs the first time an entity is synced to CouchDB.
 *
 * @param string $type
 *   The type of entity being inserted.
 * @param object $flat_entity
 *   The flattened Drupal entity being inserted.
 */
function hook_couchdb_sync_pre_insert_document($type, $flat_entity) {
  $flat_entity->created = REQUEST_TIME;
  $flat_entity->changed = REQUEST_TIME;
}

/**
 * Act on a flattened entity before it is updated in CouchDB.
 *
 * This hook only runs when an entity, already in CouchDB, is being updated.
 *
 * @param string $type
 *   The type of entity being updated.
 * @param object $flat_entity
 *   The flattened Drupal entity being updated.
 */
function hook_couchdb_sync_pre_update_document($type, $flat_entity) {
  $flat_entity->changed = REQUEST_TIME;
}

/**
 * Act on a flattened entity before it is deleted from CouchDB.
 *
 * @param string $type
 *   The type of entity being deleted.
 * @param int $id
 *   The ID of the entity being deleted.
 */
function hook_couchdb_sync_pre_deleted_document($type, $id) {
  drupal_set_message(t('The %type document with ID %id is about to be deleted from CouchDB', array('%type' => $type, '%id' => $id)));
}

/**
 * @}
 */
