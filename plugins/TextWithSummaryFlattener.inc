<?php

/**
 * @file
 * Contains TextWithSummaryFlattener.
 */

/**
 * CouchDB Sync Flattener plugin for 'text_with_summary' fields.
 */
final class TextWithSummaryFlattener implements CouchDBSyncFlattenerInterface {

  /**
   * {@inheritdoc}
   */
  public function getSupportedFieldType() {
    return 'text_with_summary';
  }

  /**
   * {@inheritdoc}
   */
  public function flatten(EntityMetadataWrapper $entity_wrapper, $field_name) {
    // Attempt to get the field value.
    if (isset($entity_wrapper->{$field_name}) && !is_null($entity_wrapper->{$field_name}->value())) {
      return $entity_wrapper->{$field_name}->value->value();
    }
    else {
      return FALSE;
    }
  }

}
