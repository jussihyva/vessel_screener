
const useSocket = false;

let	myInterval = null;
let timeFilterSec = 15 * 60;
const refreshInterval = 3000;
const timeFilter = document.getElementById("time_period");
const selectedTabCountry = document.getElementById("selected_tab_country");
const selectedTabMmsi = document.getElementById("selected_tab_mmsi");
const countryTable = document.getElementById("country_table");

window.addEventListener('DOMContentLoaded', () => {

	if (!useSocket)
	{
		timeFilterChanged();
		myInterval = setInterval(updatePage_Country, refreshInterval);
		timeFilter.onchange = timeFilterChanged;
		selectedTabCountry.onclick = openCountries;
		selectedTabMmsi.onclick = openMMSI_List;
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
	updatePage_Country();
}

function updatePage_Country() {
	const timestamp = parseInt((Date.now() / 1000) - timeFilterSec, 10);
	fetch('/table_country?timestamp='+ timestamp)
	.then((res) => {
		return res.text()
	})
	.then((text) => {
		countryTable.innerHTML = text;
	})
}

function updatePage_MMSI() {
	const timestamp = parseInt((Date.now() / 1000) - timeFilterSec, 10);
	fetch('/table_mmsi?timestamp='+ timestamp)
	.then((res) => {
		return res.text()
	})
	.then((text) => {
		countryTable.innerHTML = text;
	})
}

function openCountries()
{
	console.log("openCountries");
	countryTable.innerHTML = "";
	updatePage_Country();
	if (myInterval != null)
	{
		clearInterval(myInterval);
		myInterval = null;
	}
	myInterval = setInterval(updatePage_Country, refreshInterval);
}
function openMMSI_List()
{
	if (myInterval != null)
	{
		clearInterval(myInterval);
		myInterval = null;
	}
	myInterval = setInterval(updatePage_MMSI, refreshInterval);
	console.log("openMMSI_List");
	countryTable.innerHTML = "POO";
}
