<?php

/**
 * @file
 * API documentation for the CouchBD Sync module.
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
