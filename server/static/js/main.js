
const useSocket = false;

let current_page = null;
let	myInterval = null;
let timeFilterSec = 15 * 60;
const refreshInterval = 3000;
const timeFilter = document.getElementById("time_period");
let selectedTabCountry = document.getElementById("selected_tab_country");
let selectedTabMmsi = document.getElementById("selected_tab_mmsi");
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

$(document).ready(function() {
	$('.ui.pointing.inverted.orange.menu')
    .on('click', '.item', function() {
      if(!$(this).hasClass('dropdown')) {
        $(this)
          .addClass('active')
          .siblings('.item')
            .removeClass('active');
      }
    });
});

function timeFilterChanged() {
	timeFilterSec = timeFilter.value;
	if (current_page == 1)
	{
		updatePage_Country();
	}
	else
	{
		updatePage_MMSI();
	}
}

function updatePage_Country() {
	current_page = 1;
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
	current_page = 2;
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
	updatePage_MMSI();
	myInterval = setInterval(updatePage_MMSI, refreshInterval);
}
