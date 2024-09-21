const api = "http://127.0.0.1:5000";

window.onload = () => {
    // BEGIN CODE HERE

    // get the search button element
    const searchButton = document.getElementById("button-addon2");
    const searchInputForm = document.getElementById("searchInput");
    
    // add a click event listener to the search button
    searchButton.addEventListener("click", searchButtonOnClick);
    searchButton.addEventListener("keypress", function(event) {
        if (event.key === "Enter") { searchButtonOnClick(); }
    });

    // add a keypress listener to the search input form
    searchInputForm.addEventListener("keypress", function(event){
        if (event.key === "Enter") { event.preventDefault(); searchButtonOnClick(); }
    })

    /*
      Add product
    */

    // get the save button element
    const addProductButton = document.getElementById("addProduct");

    // Bind actions
    addProductButton.addEventListener("click", productFormOnSubmit);

    // END CODE HERE
}

searchButtonOnClick = () => {
    // BEGIN CODE HERE

    // get the search input element
    const searchInput = document.getElementById("searchInput");
  
    // get the search value from the input element
    const searchValue = searchInput.value;
    
    // make a GET request to the Flask app API with the search value as a parameter
    fetch(`${api}/search?name=${searchValue}`)
    .then(response => response.json())
    .then(data => {

      // Log the data to the console  
      console.log(data); 
      
      // get the results table body element
      const resultsTableBody = document.querySelector(".table-bordered tbody");
      
      // clear the results table body
      resultsTableBody.innerHTML = "";
      
      // iterate through each product in the search results
      data.forEach(product => {
        // create a new row element
        const row = document.createElement("tr");
        
        // create a new cell element for each product property
        const idCell = document.createElement("td");
        const nameCell = document.createElement("td");
        const productionYearCell = document.createElement("td");
        const priceCell = document.createElement("td");
        const colorCell = document.createElement("td");
        const sizeCell = document.createElement("td");
        
        // set the text content of each cell to the corresponding product property
        idCell.textContent = product.id;
        nameCell.textContent = product.name;
        productionYearCell.textContent = product.production_year;
        priceCell.textContent = product.price;
        colorCell.textContent = product.color;
        sizeCell.textContent = product.size;
        
        // append each cell to the row
        row.appendChild(idCell);
        row.appendChild(nameCell);
        row.appendChild(productionYearCell);
        row.appendChild(priceCell);
        row.appendChild(colorCell);
        row.appendChild(sizeCell);
        
        // append the row to the results table body
        resultsTableBody.appendChild(row);
      });
    })
    .catch(error => console.error(error));

    // END CODE HERE
}

productFormOnSubmit = (event) => {
    // BEGIN CODE HERE

    // Fetching the contents of the form
    const form = document.getElementById("add-product-form");
    var elements = form.elements;

    // Forming the request JSON
    var formJson = {
      "id" :              String(Math.random()),
      "name" :            elements["name"].value,
      "production_year":  Number(elements["prodYear"].value),
      "price":            Number(elements["price"].value),
      "color":            Number(elements["color"].value),
      "size":             Number(elements["size"].value)
    }

    // Building the request
    url = api + "/add-product";
    
    result = fetch(url, {
        method: "POST",
        body: JSON.stringify(formJson),
        headers: {
            "Content-type": "application/json; charset=UTF-8"
        }
    })
    // Handling the response
    .then((response) => {
      
      // If OK, erasing the values of all elements on the form and notifying the user
      if (response.status == 200){
        for (var element of elements){
        element.value = "";
        }
        alert("OK");
      
      // Debug
      } else {
        console.log("Not ok")
        console.log(response);
      }

    });

    // END CODE HERE
}
