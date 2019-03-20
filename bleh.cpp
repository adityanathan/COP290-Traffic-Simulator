void draw_cube(float px, float py, float length, float width, float height, string col)
{
	float col_r=col[0]/10;
	float col_g=col[1]/10;
	float col_b=col[2]/10;
	glTranslatef(py,0.0f,px-width+1); // (z,y,x)

	glRotatef(rquad,5.0f,0.0f,0.0f);

	// draw a cube (6 quadrilaterals)
        glBegin(GL_QUADS);				// start drawing the cube.

        // top of cube
        glColor3f(col_r,col_g,col_b);			// Set The Color To Blue
        glVertex3f( (length-1)*1.0f, 1.0f,-(width-1)*1.0f);		// Top Right Of The Quad (Top)
        glVertex3f(-(length-1)*0.0f, 1.0f,-(width-1)*1.0f);		// Top Left Of The Quad (Top)
        glVertex3f(-(length-1)*0.0f, 1.0f, (width-1)*0.0f);		// Bottom Left Of The Quad (Top)
        glVertex3f( (length-1)*1.0f, 1.0f, (width-1)*0.0f);		// Bottom Right Of The Quad (Top)

        // bottom of cube
        glColor3f(col_r,col_g,col_b);			// Set The Color To Orange
	glVertex3f( (length-1)*1.0f, height*0.0f,-(width-1)*1.0f);		// Top Right Of The Quad (Bottom)
        glVertex3f(-(length-1)*0.0f, height*0.0f,-(width-1)*1.0f);		// Top Left Of The Quad (Bottom)
        glVertex3f(-(length-1)*0.0f, height*0.0f, (width-1)*0.0f);		// Bottom Left Of The Quad (Bottom)
        glVertex3f( (length-1)*1.0f, height*0.0f, (width-1)*0.0f);		// Bottom Right Of The Quad (Bottom)

        // front of cube
        glColor3f(col_r,col_g,col_b);			// Set The Color To Red
	glVertex3f( (length-1)*1.0f, height*1.0f,-(width-1)*1.0f);		// Top Right Of The Quad (Front)
	glVertex3f(-(length-1)*0.0f, height*1.0f,-(width-1)*1.0f);		// Top Left Of The Quad (Front)
	glVertex3f( (length-1)*1.0f, height*0.0f,-(width-1)*1.0f);		// Bottom Right Of The Quad (Front)
        glVertex3f(-(length-1)*0.0f, height*0.0f,-(width-1)*1.0f);		// Bottom Left Of The Quad (Front)

        // back of cube.
        glColor3f(col_r,col_g,col_b);			// Set The Color To Yellow
	glVertex3f( (length-1)*1.0f, height*1.0f, (width-1)*0.0f);		// Top Right Of The Quad (Back)
	glVertex3f(-(length-1)*0.0f, height*1.0f, (width-1)*0.0f);		// Top Left Of The Quad (Back)
	glVertex3f( (length-1)*1.0f, height*0.0f, (width-1)*0.0f);		// Bottom Right Of The Quad (Back)
	glVertex3f(-(length-1)*0.0f, height*0.0f, (width-1)*0.0f);		// Bottom Left Of The Quad (Back)

        // left of cube
	glColor3f(col_r,col_g,col_b);			// Set The Color To Yellow
        glVertex3f((length-1)*0.0f, height*1.0f, -(width-1)*1.0f);		// Top Right Of The Quad (Left)
        glVertex3f((length-1)*0.0f, height*1.0f,-(width-1)*0.0f);		// Top Left Of The Quad (Left)
        glVertex3f((length-1)*0.0f,-height*0.0f,-(width-1)*0.0f);		// Bottom Left Of The Quad (Left)
        glVertex3f((length-1)*0.0f,-height*0.0f, -(width-1)*1.0f);		// Bottom Right Of The Quad (Left)

        // Right of cube
	glColor3f(col_r,col_g,col_b);			// Set The Color To Yellow
        glVertex3f( (length-1)*1.0f, height*1.0f,-(width-1)*1.0f);	        // Top Right Of The Quad (Right)
        glVertex3f( (length-1)*1.0f, height*1.0f, (width-1)*0.0f);		// Top Left Of The Quad (Right)
        glVertex3f( (length-1)*1.0f,-height*0.0f, (width-1)*0.0f);		// Bottom Left Of The Quad (Right)
        glVertex3f( (length-1)*1.0f,-height*0.0f,-(width-1)*1.0f);		// Bottom Right Of The Quad (Right)
        glEnd();					// Done Drawing The Cube

}
