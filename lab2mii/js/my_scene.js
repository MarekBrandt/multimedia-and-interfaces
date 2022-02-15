var container;
var camera, scene, renderer;
var width, height;
var cube;

//Tworzenie sceny

function init(){
    container = document.getElementById("div_webgl");
	width = container.offsetWidth;
	height = container.offsetHeight;

	scene = new THREE.Scene();
	camera = new THREE.PerspectiveCamera( 75, width / height, 1, 1000 );
	renderer = new THREE.WebGLRenderer();
	renderer.setSize(width, height);
	container.appendChild(renderer.domElement);
    
	//...
	// Tu nale�y skonstruowa� obiekty i doda� je do sceny 
	//...
	var texture = new THREE.VideoTexture(video); 
	var video_material = new THREE.MeshBasicMaterial( { map: texture } );

	var cube_material = new THREE.MeshPhongMaterial({color: 0x0033ff, specular: 0x555555});
	var cube_geom = new THREE.BoxGeometry(10,10,10);

	var materials = [cube_material,cube_material,video_material,cube_material,cube_material,cube_material];
	cube = new THREE.Mesh(cube_geom, new THREE.MeshFaceMaterial(materials));
	scene.add(cube);
	cube.position.set(-5,0,-20);

	var cylinder_geom = new THREE.CylinderGeometry(5,5,20,32);
	var cylinder = new THREE.Mesh(cylinder_geom, cube_material);
	scene.add(cylinder);
	cylinder.position.set(10, 0, -30);

	var light = new THREE.PointLight(0xffffff,1);
	light.position.set(-20,10,10);
	scene.add(light);

		
	render();	
}

//Rysowanie
function render() {
	cube_rotation();
	renderer.render(scene, camera);
	requestAnimationFrame(render);
}

function cube_rotation() {
	cube.rotation.x += dfi;
	cube.rotation.y += dfi;
}

//Zmiana rozmiaru
function onWindowResize() {
    width = document.getElementById("div_webgl").offsetWidth;
    height = document.getElementById("div_webgl").offsetHeight;
    camera.aspect = width / height;
    camera.updateProjectionMatrix();
    renderer.setSize(width, height);
  }
