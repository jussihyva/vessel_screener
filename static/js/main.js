
let timeFilterSec = 15 * 60;
const refreshInterval = 3000;
const $timeFilter = document.getElementById("time_period");
const $countryTable = document.getElementById("country_table");

window.addEventListener('DOMContentLoaded', () => {
	setInterval(function () { updatePage(); }, refreshInterval);
	$timeFilter.onchange = timeFilterChanged;
});

function timeFilterChanged() {
	timeFilterSec = $timeFilter.value;
	console.log('value changed', timeFilterSec);
	updatePage();
}

function updatePage() {
	const timestamp = parseInt((Date.now() / 1000) - timeFilterSec, 10);
	fetch('/table?timestamp='+ timestamp)
	.then((res) => {
		return res.text()
	})
	.then((text) => {
		$countryTable.innerHTML = text;
	})
}