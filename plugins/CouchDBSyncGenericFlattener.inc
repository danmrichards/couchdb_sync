<?php

/**
 * @file
 * Contains CouchDBSyncGenericFlattener.
 */

/**
 * Generic CouchDB Sync Flattener plugin.
 */
class CouchDBSyncGenericFlattener implements CouchDBSyncFlattenerInterface {

  /**
   * {@inheritdoc}
   */
  public function getSupportedFieldType() {
    // This plugin is a special case and is used as a fallback if no valid
    // plugin can be found for the requested field type. So this function does
    // not need to return a field type.
    return NULL;
  }

  /**
   * {@inheritdoc}
   */
  public function flatten(EntityMetadataWrapper $entity_wrapper, $field_name) {
    // Attempt to get the field value.
    if (isset($entity_wrapper->{$field_name}) && !is_null($entity_wrapper->{$field_name}->value())) {
      return $entity_wrapper->{$field_name}->value();
    }
    else {
      return FALSE;
    }
  }

}
