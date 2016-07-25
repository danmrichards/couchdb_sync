<?php

/**
 * @file
 * Contains ImageFlattener.
 */

/**
 * CouchDB Sync Flattener plugin for 'image' fields.
 */
final class ImageFlattener implements CouchDBSyncFlattenerInterface {

  /**
   * {@inheritdoc}
   */
  public function getSupportedFieldType() {
    return 'image';
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
    $parsed_value = array(
      'src' => file_create_url($value['uri']),
      'filemime' => $value['filemime'],
      'filesize' => $value['filesize'],
      'width' => $value['width'],
      'height' => $value['height'],
      'image_styles' => array(),
    );

    foreach (array_keys(image_styles()) as $image_style) {
      $parsed_value['image_styles'][$image_style] = image_style_url($image_style, $value['uri']);
    }

    return $parsed_value;
  }

}
