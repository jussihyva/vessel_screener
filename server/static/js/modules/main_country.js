const refreshInterval = 3000;

// function openCountries(countryTable, myInterval, current_page, timeFilterSec)
// {
// 	countryTable.innerHTML = "";
// 	updatePage_Country(countryTable, current_page, timeFilterSec);
// 	if (myInterval != null)
// 	{
// 		clearInterval(myInterval);
// 		myInterval = null;
// 	}
// 	myInterval = setInterval(updatePage_Country(countryTable, current_page, timeFilterSec), refreshInterval);
// }

function updatePage_Country(countryTable, timeFilterSec) {
	console.log("Filter:" + timeFilterSec);
	let timestamp = parseInt((Date.now() / 1000) - timeFilterSec, 10);
	fetch('/table_country?timestamp='+ timestamp)
	.then((res) => {
		return res.text();
	})
	.then((text) => {
		countryTable.innerHTML = text;
	});
}

export { updatePage_Country };
