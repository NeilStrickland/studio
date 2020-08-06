<?php

class studio_class extends frog {

 function get_drives($include_fixed = false) {
  $lines = array();
  $drives = array();
  exec('wmic logicaldisk get caption,description',$lines);

  foreach($lines as $line) {
   if (strlen($line) >= 7 and substr($line,0,7) == 'Caption') {
    continue;
   }

   if (substr($line,1,1) == ':') {
    $drive = new stdClass();
    $drive->letter = substr($line,0,1);
    $drive->type = trim(substr($line,2));
    if ($include_fixed || $drive->type == 'Removable Drive') {
     $drives[] = $drive;
    }
   }
  }

  $this->drives = $drives;
  return $drives;
 }

 function get_camera_videos() {
  $videos = array();
  $drives = $this->get_drives();

  $dirs = array('DCIM/100NIKON/','DCIM/101DSCIM/');
  
  foreach ($drives as $drive) {
   foreach ($dirs as $dir) {
    $full_dir = $drive->letter . ':/' . $dir;
    if (! isdir($full_dir)) { continue; }
    $files = scandir($dir);

    foreach($files as $file) {
     $full_file = $full_dir . '/' . $file;
     $ext = strtolower(pathinfo($file,PATHINFO_EXTENSION));

     if ($ext == 'mov' || $ext == 'mp4') {
      $v = $this->new_object('video');
      $v->camera_dir = $full_dir;
      $v->camera_name = $file;
      $v->file_type = $ext;
      $videos[] = $v;
     }
    }
   }
  }

  $this->camera_videos = $videos;
  return $videos;
 }
}
