<?php

/**
 * @file
 * Contains BatchProcessor.
 */

/**
 * Batch Processor plugin.
 */
final class BatchProcessor implements CouchDBSyncProcessorInterface {

  /**
   * {@inheritdoc}
   */
  public function process($entity, $type, $op = 'insert') {
    // Get the entity info.
    list($id, $vid) = entity_extract_ids($type, $entity);

    // Build the required source info to sync the entity.
    $source_entity = array(
      'id' => $id,
      'vid' => $vid,
      'type' => $type,
      'op' => $op,
    );

    // Build the batch API array.
    $batch = array(
      'operations' => array(
        array(
          'couchdb_sync_push_entity',
          array($source_entity),
        ),
      ),
      'title' => t('CouchDB: Syncing entity'),
      'error_message' => t('Could not process %type entity with an ID of %id to CouchDB for the following operation: %op', array(
        '%type' => $type,
        '%id' => $id,
        '%op' => $op,
      )),
    );

    batch_set($batch);
  }

}
