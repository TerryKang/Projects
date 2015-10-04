/**
 * ProgressBar for jQuery
 *
 * @version 1 (29. Dec 2012)
 * @author Ivan Lazarevic
 * @requires jQuery
 * @see http://workshop.rs
 *
 * @param  {Number} percent
 * @param  {Number} $element progressBar DOM element
 */
var i = 100;
var pro;
while(i>10){
	pro = setInterval(progressBar(i, $('#progressBar')),100);
	i-=5;
}
clearInterval(pro);
function progressBar(percent, $element) {
	var progressBarWidth = percent * $element.width() / 100;
	$element.find('div').animate({ width: progressBarWidth });
}