uniform sampler2D mge_texture0;
uniform sampler2D mge_texture1;

uniform vec2 lightvec;
uniform float rendertype;

float length(vec2 vec) {
	return sqrt(vec.x*vec.x + vec.y*vec.y);
}

void main() {
	vec4 data = texture2D(mge_texture1, gl_TexCoord[1].st);         // read data
	vec2 orignormal = (data.rg-0.5) * 2.0;                          // extract the normal, put it into range
	vec2 normal = (gl_ModelViewMatrix * vec4(orignormal, 0, 0)).xy; // transform normal
	normal = length(orignormal) * normalize(normal);                // preserve its distance, which is the "depth"
	float lightfact = dot(normal, lightvec);                        // compute lighting factor
	
	vec4 sprite = texture2D(mge_texture0, gl_TexCoord[0].st);       // read from sprite
	
	if (rendertype == 0.0) {                                        // regular lit sprite output
		gl_FragColor = sprite + vec4(vec3(lightfact), 0.0); 
	} else if (rendertype == 1.0) {                                 // output a grayscale image with lighting values
		float grayvalue = lightfact/2.0 + 0.5;
		gl_FragColor = vec4(vec3(grayvalue), sprite.a);
	}
}

