<?php

global $studio;

$studio->add_table(
 'uni','unis',
 array(
  'id' => array('type' => 'integer','notnull' => true),
  'name' => array('type' => 'text')
 ),
 array(),
 <<<SQL
SELECT 
 x.id,
 x.name
FROM tbl_unis x
WHERE %s
ORDER BY id

SQL
);

class uni extends frog_object {
 function __construct($id = null,$with_defaults=1) {
  global $studio;

  parent::__construct($studio,'uni',$id,$with_defaults);
 }
}


