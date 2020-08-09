import { openCountries, updatePage_Country } from './main_country.js';
import { openMMSI_List, updatePage_MMSI } from './main_mmsi.js';

const useSocket = false;

let current_page = 1;
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
		selectedTabCountry.onclick = function() {current_page = openCountries(countryTable, myInterval, timeFilterSec);};
		selectedTabMmsi.onclick = function() {current_page = openMMSI_List(countryTable, myInterval, timeFilterSec);};
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
	console.log(current_page);
	if (current_page == 1)
	{
		updatePage_Country(countryTable, timeFilterSec);
	}
	else
	{
		updatePage_MMSI(countryTable, timeFilterSec);
	}
}
