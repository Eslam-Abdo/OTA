<?php



    if(isset($_FILES['fileToUpload']))
    {
    	$files = glob('uploads/*'); // get all file names
    	foreach($files as $file)
    	{
        	// iterate files
    	  if(is_file($file))
          {
            unlink($file); // delete file
          }
    	}
    }

    $errors= array();
    $file_name = $_FILES['fileToUpload']['name'];
    $file_size = $_FILES['fileToUpload']['size'];
    $file_tmp = $_FILES['fileToUpload']['tmp_name'];
    $file_type = $_FILES['fileToUpload']['type'];
    $file_ext=strtolower(end(explode('.',$_FILES['fileToUpload']['name'])));

    $expensions= array("hex");


    if(in_array($file_ext,$expensions)=== false)
    {
      $errors[]="extension not allowed, please choose a HEX file.<br>";
    }

    if($file_size > 500000)
    {
      $errors[]='File size must be excately 500kb';
    }

    if(empty($errors)==true)
    {
      move_uploaded_file($file_tmp,"uploads/".$file_name);
      echo "Success";
      echo "The file ". htmlspecialchars( basename( $_FILES["fileToUpload"]["name"])). " has been uploaded.";;

    header ("Location: done_upload.html" );
    }
    else
    {
      echo "Sorry, there was an error uploading your file.";
      echo "<br>";
      print_r($errors);
    }
?>
