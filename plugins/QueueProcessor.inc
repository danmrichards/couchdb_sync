<?php

/**
 * @file
 * Contains QueueProcessor.
 */

/**
 * Queue Processor plugin.
 */
final class QueueProcessor implements CouchDBSyncProcessorInterface {

  /**
   * {@inheritdoc}
   */
  public function process($entity, $type, $op = 'insert') {
    // Get the entity info.
    list($id, $vid) = entity_extract_ids($type, $entity);

    // Build the queue item.
    $queue_item = array(
      'id' => $id,
      'vid' => $vid,
      'type' => $type,
      'op' => $op,
    );

    // Load the CouchDB Sync.
    $queue = DrupalQueue::get(COUCHDB_SYNC_ENTITY_QUEUE);

    // Push the item into the queue and check it was successful.
    if (!$queue->createItem($queue_item)) {
      throw new CouchDBSyncException(t('Could not process %type entity with an ID of %id to CouchDB for the following operation: %op', array(
        '%type' => $type,
        '%id' => $id,
        '%op' => $op,
      )));
    }
  }

}
