<?php

global $studio;

$studio->add_table(
 'video','videos',
 array(
  'id' => array('type' => 'integer','notnull' => true),
  'course_id' => array('type' => 'integer'),
  'camera_dir' => array('type' => 'text'),
  'camera_name' => array('type' => 'text'),
  'short_name' => array('type' => 'text'),
  'file_type' => array('type' => 'text'),
  'title' => array('type' => 'text'),
  'youtube_id' => array('type' => 'text'),
  'kaltura_id' => array('type' => 'text'),
  'length' => array('type' => 'integer'),
  'sort_order' => array('type' => 'integer')
 ),
 array(
  'course_code' => array('type' => 'text'),
  'course_name' => array('type' => 'text'),
  'uni_name' => array('type' => 'text')
 ),
 <<<SQL
SELECT 
 x.id,
 x.course_id,
 c.code AS course_code,
 c.name AS course_name,
 u.name AS uni_name,
 x.camera_dir,
 x.camera_name,
 x.short_name,
 x.file_type,
 x.title,
 x.youtube_id,
 x.kaltura_id,
 x.length,
 x.sort_order
FROM tbl_videos x 
 LEFT JOIN tbl_courses c ON x.course_id=c.id
  LEFT JOIN tbl_unis u ON c.uni_id=u.id
WHERE %s
 ORDER BY u.id,x.sort_order,x.title,x.id
SQL
);

class video extends frog_object {
 function __construct($id = null,$with_defaults=1) {
  global $studio;

  parent::__construct($studio,'video',$id,$with_defaults);
 }

 function full_camera_name() {
  return $this->camera_dir . $this->camera_name;
 }

 function full_local_name() {
  global $studio;
  
  return $studio->video_dir . '/' . $this->short_name . '.' . $this->file_type;
 }
 
 function set_short_name($name = '') {
  if (! $this->short_name) { $this->short_name = $name; }
  if (! $this->short_name) {
   $this->short_name = pathinfo($this->camera_name,PATHINFO_FILENAME);
  } 
 }
 
 function import_and_flip($name = '') {
  $this->set_short_name($name);

  $cmd = 'ffmpeg -i "' .
       $this->full_camera_name() .
       '" -vf hflip -c:a copy "' .
       $this->full_local_name() . '"';

  exec($cmd);
 }
}


