//
//  Shader.fsh
//  R-Type
//
//  Created by Gael du Plessix on 21/12/12.
//  Copyright (c) 2012 EPITECH. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
