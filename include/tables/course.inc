<?php

global $studio;

$studio->add_table(
 'course','courses',
 array(
  'id' => array('type' => 'integer','notnull' => true),
  'uni_id' => array('type' => 'integer'),
  'code' => array('type' => 'text'),
  'name' => array('type' => 'text')
 ),
 array(
  'uni_name' => array('type' => 'text')
 ),
 <<<SQL
SELECT 
 x.id,
 x.uni_id,
 u.name AS uni_name,
 x.code,
 x.name
FROM tbl_courses x 
 LEFT JOIN tbl_unis u ON x.uni_id=u.id
WHERE %s
 ORDER BY x.uni_id,x.code

SQL
);

class course extends frog_object {
 function __construct($id = null,$with_defaults=1) {
  global $studio;

  parent::__construct($studio,'course',$id,$with_defaults);
 }
}


