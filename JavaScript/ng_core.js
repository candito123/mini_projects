function barOpen() {
    document.getElementById("sidebar").style.display = "block";
}
function barClose() {
    document.getElementById("sidebar").style.display = "none";
}

function mouseOutItem(obj){
    findIndicesOfSameContentAndRunFunc(obj, 1);
    // console.log('add nl [2]', nodeList[2]);

}
function mouseOverItem(obj){
    findIndicesOfSameContentAndRunFunc(obj, 0);
}

//acc sidebar
function getAccSidebar() {
    var x = document.getElementById("accSidebar");

    if (x.className.indexOf("show") == -1) {
            x.className += " show";
            x.previousElementSibling.className += " green";
    } else {
            x.className = x.className.replace(" show", "");
            x.previousElementSibling.className =
            x.previousElementSibling.className.replace(" green", "");
        }
}
//acc in main
function getAcc1() {
    var x = document.getElementById("acc1");

    if (x.className.indexOf("show") == -1) {
            x.className += " show";
            x.previousElementSibling.className += " green";
    } else {
            x.className = x.className.replace(" show", "");
            x.previousElementSibling.className =
            x.previousElementSibling.className.replace(" green", "");
        }
}
function getAcc2() {
    var x = document.getElementById("acc2");

    if (x.className.indexOf("show") == -1) {
            x.className += " show";
            x.previousElementSibling.className += " green";
    } else {
            x.className = x.className.replace(" show", "");
            x.previousElementSibling.className =
            x.previousElementSibling.className.replace(" green", "");
        }
}
function getAcc3() {
    var x = document.getElementById("acc3");

    if (x.className.indexOf("show") == -1) {
            x.className += " show";
            x.previousElementSibling.className += " green";
    } else {
            x.className = x.className.replace(" show", "");
            x.previousElementSibling.className =
            x.previousElementSibling.className.replace(" green", "");
        }
}
function getAcc4() {
    var x = document.getElementById("acc4");

    if (x.className.indexOf("show") == -1) {
            x.className += " show";
            x.previousElementSibling.className += " green";
    } else {
            x.className = x.className.replace(" show", "");
            x.previousElementSibling.className =
            x.previousElementSibling.className.replace(" green", "");
        }
}
function getAcc5() {
    var x = document.getElementById("acc5");

    if (x.className.indexOf("show") == -1) {
            x.className += " show";
            x.previousElementSibling.className += " green";
    } else {
            x.className = x.className.replace(" show", "");
            x.previousElementSibling.className =
            x.previousElementSibling.className.replace(" green", "");
        }
}
function getAcc6() {
    var x = document.getElementById("acc6");

    if (x.className.indexOf("show") == -1) {
            x.className += " show";
            x.previousElementSibling.className += " green";
    } else {
            x.className = x.className.replace(" show", "");
            x.previousElementSibling.className =
            x.previousElementSibling.className.replace(" green", "");
        }
}
function getAcc7() {
    var x = document.getElementById("acc7");

    if (x.className.indexOf("show") == -1) {
            x.className += " show";
            x.previousElementSibling.className += " green";
    } else {
            x.className = x.className.replace(" show", "");
            x.previousElementSibling.className =
            x.previousElementSibling.className.replace(" green", "");
        }
}

//sticky navbar, sidebar
window.addEventListener("scroll", getNavSticky);
window.addEventListener("scroll", getSideSticky);

var navbar = document.getElementById("navbar");
var navSticky = navbar.offsetTop;

function getNavSticky() {
    if (window.pageYOffset >= navSticky) {
        navbar.classList.add("sticky");
    } else {
        navbar.classList.remove("sticky");
    }
}
var sidebar = document.querySelector(".sidebar");
var sideSticky = sidebar.offsetTop;

function getSideSticky() {
    if (window.pageYOffset >= navSticky) {
        sidebar.classList.add("sticky");
        sidebar.style.top = navbar.offsetHeight+ "px";
    } else {
        sidebar.classList.remove("sticky");
        sidebar.style.top = navbar.offsetHeight + navSticky + "px";
    }
}


// modal (id 1) for video
var modal = document.getElementById("modal1");
var modalContent = document.querySelector("#modal1 .modal-content"); //test
var video = document.querySelector("#modal1 .video");
// modal (id 1) open button
var modal1Btn = document.getElementById("modal1Btn");
// This span to close the modal (works in general)
var span = document.getElementsByClassName("close")[0];
// open the modal (id 1) and expand the content size
    /*
    modal1Btn.onclick = function() {
        modal.style.display = "block";
        modalContent.style.height = "80%";
        modalContent.style.textAlign = "center";
        video.style.marginTop = "5px";
        video.style.height = "100%";
        video.style.width = "100%";
    }
    */
// close the modal by click button
    //     span.onclick = function() {
    //     modal.style.display = "none";
    // }
// close the modal by outside click

window.onclick = function(event) {
    if (event.target == modal) {
        modal.style.display = "none";
    }
}
//remove veil when the page is fully loaded
window.onload = function(){
    document.querySelector(".veil").classList.remove("z-index-5");
}

// <a href="#"
//     class="bar-item button darkForest light-up-if-same-name"
//     onmouseout="mouseOutItem(this)" onmouseover="mouseOverItem(this)">
//     Link 1
// </a>

var nodeList = document.querySelectorAll(".light-up-if-same-name")
var lookUp = [[nodeList[0].innerHTML, 0],];
for (var i=1; i<nodeList.length; i++){
    var content = nodeList[i].innerHTML
    var lookUpLen = lookUp.length

    for (var j=0; j<lookUpLen; j++){
        if (lookUp[j][0]==content){
            lookUp[j].push(i)
            break;
        } else if (j+1==lookUpLen && lookUp[j][0]!=content) {
            lookUp[j+1] = [content, i]
        }
    }
}

// console.log('lookup here', lookUp);

function findIndicesOfSameContentAndRunFunc(obj, addOrRemove){
    for (var i=0; i<lookUp.length; i++){
        if (obj.innerHTML == lookUp[i][0]){
            for (var j=1; j< lookUp[i].length; j++){
                let index = lookUp[i][j];
                if (addOrRemove == 0){
                    nodeList[index].classList.add("light-up");
                    // console.log('add', nodeList[index]);
                }else{
                    nodeList[index].classList.remove("light-up");
                    // nodeList[index].remove("light-up");
                    // console.log('remove', nodeList[index]);
                }

            }
            break;
        }
    }
}
