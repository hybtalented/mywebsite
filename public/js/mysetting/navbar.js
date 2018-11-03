$(document).ready(
    function(){
        $(".mynavbar").html('\
    <nav class="navbar navbar-expand-lg navbar-dark bg-primary" role="navigation">\
        <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNavDropdown" aria-controls="navbarNavDropdown" aria-expanded="false" aria-label="Toggle navigation">\
            <span class="navbar-toggler-icon"></span>\
        </button>\
        <div class="collapse navbar-collapse float-left" id="navbarNavDropdown">\
            <ul class="navbar-nav mr-auto">\
                <li class="nav-item" id="i_index"><a href="/index.html" class="nav-link"> <span class="gybphicon glyphicon-index"></span> 主页</a></li>\
                <li class="nav-item" id="i_face"><a href="/index.html" class="nav-link"> <span class="gybphicon glyphicon-index"></span> 人脸识别</a></li>\
                <li class="nav-item" id="i_blog"><a href="/Blog" class="nav-link"> <span class="gybphicon glyphicon-index"></span> 博客 </a></li>\
            </ul>\
        </div>\
         <ul class="navbar-nav mr-auto float-right">\
            <li class="nav-item" id="i_login"> <a href="/User/login" class="nav-link"><span class="glyphicon glyphicon-user"></span> 登录 </a> </li>\
            <li class="nav-item" id="i_register"> <a href="/User/userregister" class="nav-link"><span class="glyphicon glyphicon-log-in"></span> 注册</a></li>\
        </ul>\
    </nav>')
    }); 