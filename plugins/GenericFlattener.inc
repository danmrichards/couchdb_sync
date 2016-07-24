<?php

/**
 * @file
 * Contains GenericFlattener.
 */

/**
 * Generic CouchDB Sync Flattener plugin.
 */
final class GenericFlattener implements CouchDBSyncFlattenerInterface {

  /**
   * {@inheritdoc}
   */
  public function getSupportedFieldType() {
    // This plugin is a special case and is used as a fallback if no valid
    // plugin can be found for the requested field type.
    return COUCHDB_SYNC_GENERIC_FIELD_INDICATOR;
  }

  /**
   * {@inheritdoc}
   */
  public function flatten(EntityMetadataWrapper $entity_wrapper, $field_name, $multiple = FALSE) {
    // Attempt to get the field value.
    if (isset($entity_wrapper->{$field_name}) && !is_null($entity_wrapper->{$field_name}->value())) {
      return $entity_wrapper->{$field_name}->value();
    }
    else {
      return FALSE;
    }
  }

}
