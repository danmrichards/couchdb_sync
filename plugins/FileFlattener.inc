<?php

/**
 * @file
 * Contains FileFlattener.
 */

/**
 * CouchDB Sync Flattener plugin for 'file' fields.
 */
final class FileFlattener implements CouchDBSyncFlattenerInterface {

  /**
   * {@inheritdoc}
   */
  public function getSupportedFieldType() {
    return 'file';
  }

  /**
   * {@inheritdoc}
   */
  public function flatten(EntityMetadataWrapper $entity_wrapper, $field_name) {
    // Attempt to get the field value.
    if (isset($entity_wrapper->{$field_name}) && !is_null($entity_wrapper->{$field_name}->value())) {
      // For images strip out some of the core data and append image style URLs.
      $raw_value = $entity_wrapper->{$field_name}->value();

      return array(
        'src' => file_create_url($raw_value['uri']),
        'filemime' => $raw_value['filemime'],
        'filesize' => $raw_value['filesize'],
        'description' => $raw_value['description'],
      );
    }
    else {
      return FALSE;
    }
  }

}
