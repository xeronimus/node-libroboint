/**
 *
 * @param ri
 * @param theLoop
 * @param interval
 */
function loop(ri, theLoop, interval = 50) {
    if (!ri.hasInterface()) {
        console.error('not connected, will not loop');
    }

    let intervalH = setInterval(theLoop.bind(theLoop, endCb), interval);

    function endCb() {
        clearInterval(intervalH);
        ri.close();
    }
}

module.exports = {
    loop,
};
