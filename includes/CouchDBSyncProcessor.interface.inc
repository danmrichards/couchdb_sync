<?php

/**
 * @file
 * Contains CouchDBSyncProcessorInterface.
 */

/**
 * Interface that all processor plugins need to implement.
 *
 * Responsible for defining the method in which entities are processed and
 * synced across to CouchDB.
 */
interface CouchDBSyncProcessorInterface {

  /**
   * Process an entity and sync it to CouchDB.
   *
   * @param object $entity
   *   The entity object.
   * @param string $type
   *   The type of entity being saved (i.e. node, user, comment).
   * @param string $op
   *   The operation that needs to be performed in CouchDB.
   */
  public function process($entity, $type, $op = 'insert');

}
