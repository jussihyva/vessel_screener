const refreshInterval = 3000;

function openMMSI_List(countryTable, myInterval, timeFilterSec)
{
	let current_page;

	current_page = 2;
	updatePage_MMSI(countryTable, timeFilterSec);
	if (myInterval != null)
	{
		clearInterval(myInterval);
		myInterval = null;
	}
	myInterval = setInterval(updatePage_MMSI(countryTable, timeFilterSec), refreshInterval);
	current_page = 2;
	return(current_page);
}

function updatePage_MMSI(countryTable, timeFilterSec) {
	let timestamp = parseInt((Date.now() / 1000) - timeFilterSec, 10);
	fetch('/table_mmsi?timestamp='+ timestamp)
	.then((res) => {
		return res.text()
	})
	.then((text) => {
		countryTable.innerHTML = text;
	})
}

export { openMMSI_List, updatePage_MMSI };
