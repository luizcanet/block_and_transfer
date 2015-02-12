<?php
/**
 * @file
 * block_and_transfer.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function block_and_transfer_default_rules_configuration() {
  $items = array();
  $items['rules_block_and_transfer_content'] = entity_import('rules_config', '{ "rules_block_and_transfer_content" : {
      "LABEL" : "Block and Transfer Content",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "user_update" : [] },
      "IF" : [ { "user_is_blocked" : { "account" : [ "account" ] } } ],
      "DO" : [
        { "mail" : {
            "to" : "[account:mail]",
            "subject" : "Account Blocked",
            "message" : "Your account was blocked!\\r\\n\\r\\n[site:name] Team",
            "language" : [ "" ]
          }
        },
        { "drupal_message" : { "message" : "This user was blocked. You can transfer their content to another user." } },
        { "redirect" : { "url" : "user\\/[account:uid]\\/transfer-content" } }
      ]
    }
  }');
  $items['rules_notify_new_author'] = entity_import('rules_config', '{ "rules_notify_new_author" : {
      "LABEL" : "Notify New Author",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_update" : [] },
      "IF" : [
        { "NOT data_is" : {
            "data" : [ "node-unchanged:author:uid" ],
            "value" : [ "node:author:uid" ]
          }
        }
      ],
      "DO" : [
        { "mail" : {
            "to" : [ "node:author:mail" ],
            "subject" : "Your New Content",
            "message" : "You have a new content in [site:name]:\\r\\n\\r\\n[node:title]\\r\\n\\r\\n[site:name] Team",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  return $items;
}
