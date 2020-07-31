
const useSocket = true;

let timeFilterSec = 15 * 60;
const refreshInterval = 3000;
const timeFilter = document.getElementById("time_period");
const countryTable = document.getElementById("country_table");

window.addEventListener('DOMContentLoaded', () => {

	if (!useSocket)
	{
		setInterval(function () { updatePage(); }, refreshInterval);
		timeFilter.onchange = timeFilterChanged;
		return ;
	}

	const ws = new WebSocket('ws://localhost:8001/ws');
	ws.onopen = function(event) {
		console.log('WebSocket connection opened');
	}
	ws.onerror = function(error) {
		console.log(error);
	}
	ws.onmessage = function(event) {
		console.log(event.data);
	}

});

function timeFilterChanged() {
	timeFilterSec = timeFilter.value;
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
		countryTable.innerHTML = text;
	})
}