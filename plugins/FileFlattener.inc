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
  public function flatten(EntityMetadataWrapper $entity_wrapper, $field_name, $multiple = FALSE) {
    // Attempt to get the field value.
    if (isset($entity_wrapper->{$field_name}) && !is_null($entity_wrapper->{$field_name}->value())) {
      // For images strip out some of the core data and append image style URLs.
      $raw_value = $entity_wrapper->{$field_name}->value();

      if ($multiple !== FALSE) {
        return array_map(array($this, 'parseValue'), $raw_value);
      }

      return $this->parseValue($raw_value);
    }
    else {
      return FALSE;
    }
  }

  /**
   * Parse a single field value into the desired format.
   *
   * @param array $value
   *   The raw value of the field.
   *
   * @return array
   *   Parsed field value array.
   */
  protected function parseValue($value) {
    return array(
      'src' => file_create_url($value['uri']),
      'filemime' => $value['filemime'],
      'filesize' => $value['filesize'],
      'description' => $value['description'],
    );
  }

}
