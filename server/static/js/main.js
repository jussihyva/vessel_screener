import { updatePage_Country } from './modules/main_country.js';

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
		myInterval = setInterval(updatePage_Country(countryTable, timeFilterSec), refreshInterval);
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
		updatePage_Country(countryTable, timeFilterSec);
	}
	else
	{
		updatePage_MMSI();
	}
}

function updatePage_MMSI() {
	let timestamp = parseInt((Date.now() / 1000) - timeFilterSec, 10);
	fetch('/table_mmsi?timestamp='+ timestamp)
	.then((res) => {
		return res.text()
	})
	.then((text) => {
		countryTable.innerHTML = text;
	})
}

function openMMSI_List()
{
	console.log("Open MMSI:" + current_page);
	current_page = 2;
	updatePage_MMSI();
	if (myInterval != null)
	{
		clearInterval(myInterval);
		myInterval = null;
	}
	myInterval = setInterval(updatePage_MMSI, refreshInterval);
}

function openCountries()
{
	console.log("Open Country:" + current_page);
	countryTable.innerHTML = "";
	current_page = 1;
	updatePage_Country(countryTable, timeFilterSec);
	if (myInterval != null)
	{
		clearInterval(myInterval);
		myInterval = null;
	}
	myInterval = setInterval(updatePage_Country(countryTable, timeFilterSec), refreshInterval);
}
