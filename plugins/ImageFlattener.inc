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

      // TODO: Implement multiple value handling.
      $value = array(
        'src' => file_create_url($raw_value['uri']),
        'filemime' => $raw_value['filemime'],
        'filesize' => $raw_value['filesize'],
        'width' => $raw_value['width'],
        'height' => $raw_value['height'],
        'image_styles' => array(),
      );

      foreach (array_keys(image_styles()) as $image_style) {
        $value['image_styles'][$image_style] = image_style_url($image_style, $raw_value['uri']);
      }

      return $value;
    }
    else {
      return FALSE;
    }
  }

}
