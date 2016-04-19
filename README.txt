INTRODUCTION
------------
This modules provides an opinionated integration with CouchDB; allowing you to
synchronise entities from Drupal into a CouchDB installation. The entities can
then be quickly accessed (via the CouchDB API) by apps, decoupled front ends and
and basically anything with a HTTP client. CouchDB API documentation can be 
found at http://docs.couchdb.org/.

The 'opinionated' part of this module refers to the fact it is not just encoding
a raw entity with JSON and calling it a day. Drupal entities are very verbose
and parsing through them is a pain at the best of times. This module will
'flatten' the entity as much as possible with the goal of improving the dev
experience for anyone consuming the data.

DISCLAIMER
----------
This module is not intended to be a content staging solution. It is designed to
be a one way process, from Drupal to CouchDB, and that will never change. If
you want something to sync entities to and from CouchDB then you should look
at the Deploy project - http://www.drupaldeploy.org.

ENTITY FLATTENING
-----------------
The mantra of this module is to flatten entities to make them easy to work with.
Doing this involves following a few rules of thumb:

  * Data should be accessible, and usable, no more than 2 levels deep. No more
    entity->field[language][0]->value['safe_value']
  * Collapse arrays with incremental keys into simple JSON lists.
  * Just Enough Data - If the end consumer doesn't need the data, then don't
    include it.

REQUIREMENTS
------------
This module requires the following modules:
  * CouchDB Integration (https://drupal.org/project/couchdb)
  * Chaos tool suite (https://drupal.org/project/ctools)
  * Entity API (https://www.drupal.org/project/entity)

INSTALLATION
------------
  * Enable the CouchDB Sync module (https://www.drupal.org/documentation/install/modules-themes/modules-7).
  * Clear cache.

CONFIGURATION
-------------
At this stage there is no configuration UI, but it will come at some stage. The
scope of which will be to choose which entity types and bundles that get synced
to CouchDB. Also there is scope for choosing the method of pushing the data;
deferred via queue or instant.

MAINTAINERS
-----------
Current maintainers:
  * Dan Richards - https://www.drupal.org/user/3157375

This project has been sponsored by:
  * LUSH Digital - https://www.drupal.org/node/2529922
    In order for us to become a company of the future and clear cosmetic leader
    we are putting the internet at the heart of our business. It's time for Lush
    to be at the forefront of digital and revolutionise the cosmetics industry.

    Lush Digital enables technology to connect people throughout our community
    and build relationships bringing customer to the heart of our business.