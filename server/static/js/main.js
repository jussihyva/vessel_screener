import { updatePage_Country } from './main_country.js';
import { updatePage_MMSI } from './main_mmsi.js';

const useSocket = false;

let current_page = 1;
let timeFilterSec = 15 * 60;
const refreshInterval = 5000;
const timeFilter = document.getElementById("time_period");
let selectedTabCountry = document.getElementById("selected_tab_country");
let selectedTabMmsi = document.getElementById("selected_tab_mmsi");
const countryTable = document.getElementById("country_table");
const messageStatisticsTable = document.getElementById("message_statistics_table");

window.addEventListener('DOMContentLoaded', () => {

	if (!useSocket)
	{
		timeFilterChanged();
		timeFilter.onchange = timeFilterChanged;
		selectedTabCountry.onclick = function()
		{
			current_page = 1;
			openCountries(countryTable, messageStatisticsTable, timeFilterSec);
		};
		selectedTabMmsi.onclick = function()
		{
			current_page = 2;
			openMMSI_List(countryTable, messageStatisticsTable, timeFilterSec);
		};
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
		openCountries(countryTable, messageStatisticsTable);
	}
	else
	{
		openMMSI_List(countryTable, messageStatisticsTable);
	}
}

function openCountries(countryTable, messageStatisticsTable)
{
	if (current_page == 1)
	{
		updatePage_Country(countryTable, messageStatisticsTable, timeFilterSec);
		setTimeout(function()
		{
			openCountries(countryTable, messageStatisticsTable);
		}, refreshInterval);
	}
	return ;
}

function openMMSI_List(countryTable, messageStatisticsTable)
{
	if (current_page == 2)
	{
		updatePage_MMSI(countryTable, messageStatisticsTable, timeFilterSec);
		setTimeout(function()
		{
			openMMSI_List(countryTable, messageStatisticsTable);
		}, refreshInterval);
	}
	return ;
}
