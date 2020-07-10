var component;
var sprite;
var parent;

function createObjects(path, root) {
    parent = root
    component = Qt.createComponent(path);
    console.log(component, component.status);
    if (component.status === Component.Ready)
        finishCreation();
    else
        component.statusChanged.connect(finishCreation);
}

function finishCreation() {
    console.log("finishCreation");
    if (component.status === Component.Ready) {
        sprite = component.createObject(parent);
        if (sprite === null) {
            // Error Handling
            console.log("Error creating object");
        }
    } else if (component.status === Component.Error) {
        // Error Handling
        console.log("Error loading component:", component.errorString());
    }
    console.log("Window created");
}
