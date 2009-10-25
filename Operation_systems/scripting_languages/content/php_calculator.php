<h1>Calculator</h1>
<?php
if ($submit)
{
   if ($operator == '*') {
       echo $numa * $numb;
   } elseif ($operator == '/') {
       echo $numa / $numb;
   } elseif ($operator == '+') {
       echo $numa + $numb;
   } elseif ($operator == '-') {
       echo $numa - $numb;
   }
} else { ?>
<form method="POST" action="<?php $_SERVER['PHP_SELF']; ?>">
  <input type="text" name="numa" size="10">
  <input type="text" name="operator" size="2">
  <input type="text" name="numb" size="10">
  <input type="submit" value="Calculate" name="submit">
</form>
<?php } ?>
