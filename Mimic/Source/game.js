$(document).ajaxSend(function() {
    $.mobile.loading( 'show');
});
$(document).ajaxComplete(function() {
    $.mobile.loading( 'hide');
});
var app = {
    // Application Constructor
    initialize: function() {
	//alert('0');
        this.bindEvents();
    },
    // Bind Event Listeners
    //
    // Bind any events that are required on startup. Common events are:
    // 'load', 'deviceready', 'offline', and 'online'.
    bindEvents: function() {
        document.addEventListener('deviceready', this.onDeviceReady, false);
    },
    // deviceready Event Handler
    //
    // The scope of 'this' is the event. In order to call the 'receivedEvent'
    // function, we must explicitly call 'app.receivedEvent(...);'
    onDeviceReady: function() {
	//alert('3');
        sounds.init();
	//alert('2');
        sounds.bgmStart();
        //sounds.effect[1].play();
        //app.receivedEvent('deviceready');
	navigator.splashscreen.hide();
	//document.addEventListener('pause', this.onPause, false);
	//document.addEventListener("resume", this.onResume, false); 

        
    }
    // Update DOM on a Received Event
};
app.initialize();

function onPause(){
	if($.mobile.activePage.is('#game')){
		allStop();
		$( "#pop_menu" ).popup( "open", {positionTo: 'window', transition: "pop"});
	}else if($.mobile.activePage.is('#main') || $.mobile.activePage.is('#scoreboard')){
		sounds.bgmStop();
	}
}
function onResume(){
	if($.mobile.activePage.is('#main') || $.mobile.activePage.is('#scoreboard')){
		sounds.bgmStart();
	}
}

function init(){
	game.init();
	character.init();
	energyBar.init();
}

$(document).ready(function() {
	$(window).bind("orientationchange resize pageshow", resizing);
	document.addEventListener('pause', onPause, false);
	document.addEventListener("resume", onResume, false);
	document.addEventListener("backbutton", function(e){
		e.preventDefault();
		if($.mobile.activePage.is('#main')){
		    navigator.app.exitApp();
		}
		else if($.mobile.activePage.is('#game')){
			allStop();
			$( "#pop_menu" ).popup( "open", {positionTo: 'window', transition: "pop"});
		}
		else if($.mobile.activePage.is('#scoreboard')){
			parent.history.back();
		}
	}, false);
	//document.addEventListener('deviceready', function(){alert('ready');}, false);
	//sounds.init();
	//alert('a');
	//sounds.bgmStart();
	$(document).on("pagebeforeshow","#game",function(){
		init();
		$('.username').show();
		$('.username').val('');
		$('.submit').show();
	});
	$(document).on("pagebeforeshow","#gameover",function(){
		$('#score_num').html(game.score);
		//allStop();
	});
	$(document).on("pagebeforeshow", "#scoreboard", function(){
		$.ajax({
			url: 'http://togs.comeze.com/projecta/test.php',
			success: function(result) {
				//alert(result);
				$('#score_table').html(result);
			},
			error: function(error){
				//alert('fail');
				alert(error);
			}
		});
	});
	$(document).on("pagecreate pageshow","#main",function(){
		sounds.bgmStart();
		//allStop();
	});
	$(document).on("pagecreate pageshow","#scoreboard",function(){
		sounds.bgmStart();
		//allStop();
	});
	$(document).on("pageshow","#game",function(){
		sounds.bgmStop();
		energyBar.resize();
		$('#start').off('vmousedown').on('vmousedown',function(){
			game.start();
		});
		$('.btns').off('vmousedown').on('vmousedown',function()
		{
			var idx = $(this).val();
			game.touch(idx);
			if(game.playing){
				$(this).attr('src','images/pbtn'+idx+'.png');
			}
			return false;
		});
		$('.btns').off('vmouseup').on('vmouseup',function()
		{
			if(game.playing){
				$(this).attr('src','images/btn'+$(this).val()+'.png');
			}
			game.release();
			return false;
		});
			$('.btns').off('vclick').on('vclick',function()
		{
			return false;
		});
		$('#start').off('vclick').on('vclick',function()
		{
			return false;
		});
	});
	$('.submit').click(function(){
		var name = $('.username').val();
		var score = game.score;
		if (name!='') {
			$.ajax({
				type:'POST',
				url: 'http://togs.comeze.com/projecta/add_name.php',
				data: 'name=' + name + '&score=' + score,
				success: function() {
					$('.username').hide();
					$('.submit').hide();
					$.mobile.changePage( "#scoreboard", { transition: "pop", changeHash: true, role: 'dialog'});
				},
				error: function(error){
					alert('fail');
					alert(error);
				}
			});
		}
	});
	$('#restart1').click(function(){
		$.mobile.changePage( "#game", { transition: "flip", changeHash: true});
	});
	$('#restart2').click(function(){
		$( "#pop_menu" ).popup( "close");
		game.reset();
		init();
	});
	$('#resume').click(function(){
		$( "#pop_menu" ).popup( "close");
		if (!game.started || (game.starting!=null && game.started)) {
			game.reset();
			init();
		}else{
			energyBar.run();
			game.random();
		}
	})
	$('.toMain').click(function(){
		$.mobile.changePage( "#main", { transition: "flip", changeHash: true });
	});
	$('.toExit').click(function(){
		navigator.app.exitApp();
	});
	$(document).off("pagebeforehide","#game").on("pagebeforehide","#game",game.reset);
	//document.addEventListener("backbutton", function() {return false;}, false);
	/*
	$(".custom-btn").on("touchstart", function(e) {
		$(this).css('transform','scale(0.9)');
	});
	$(".custom-btn").on("touchend touchcancel", function(e) {
		$(this).css('transform','scale(1.0)');
	});*/
});

function scorebd(){}
var sounds = new Sounds();
 function Sounds(){
	this.init = function (){
		/*
		this.bgm = new Audio("/android_asset/www/sounds/main_bgm.mp3");
		this.volume = .25;
		this.bgm.loop = true;
		this.bgm.load();
		this.effect=[];
		for(i=1;i<=5;i++){
			this.effect[i] = new Audio("/android_asset/www/sounds/action"+i+".wav");
			this.effect[i].volume = .25;
			this.effect[i].load();
		}*/
		this.playing = false;
		var src = "/android_asset/www/sounds/main_bgm.mp3";
		this.bgm = new Media(src, onSuccess, onError, bgmLoop);
		this.effect=[];
		for(i=1;i<=5;i++){
			src = "/android_asset/www/sounds/action"+i+".wav";
			this.effect[i] = new Media(src, onSuccess, onError);
		}
		this.start=[];
		for(i=0;i<=3;i++){
			src = "/android_asset/www/sounds/start_"+i+".mp3";
			this.start[i] = new Media(src, onSuccess, onError);
		}
		src = "/android_asset/www/sounds/nice.wav";
		this.nice = new Media(src, onSuccess, onError);
		src = "/android_asset/www/sounds/timeup.wav";
		this.timeup = new Media(src, onSuccess, onError);
	};
	this.bgmStart = function(){
		if (!this.playing) {
			this.bgm.play();
			this.playing = true;
		}
	};
	this.bgmStop = function(){
		this.playing = false;
		this.bgm.stop();
	};
	this.skip = function(){
	};
 }
 
// onSuccess Callback
// 
function onSuccess() {
	console.log("recordAudio():Audio Success");
}

// onError Callback 
//
function onError(error) {
	//code
}
//bgm loop
function bgmLoop(status) {
	if (status == Media.MEDIA_STOPPED && sounds.playing) {
		sounds.bgm.play();
	}
}

var resizing = function() {
    /* Some orientation changes leave the scroll position at something
     * that isn't 0,0. This is annoying for user experience. */
    scroll(0, 0);

    /* Calculate the geometry that our content area should take */
    var header = $(".header:visible");
    var footer = $(".footer:visible");
    var content = $(".content:visible");
    var viewport_height = $.mobile.getScreenHeight();
    var content_height = viewport_height - header.outerHeight() - footer.outerHeight();
    
    /* Trim margin/border/padding height */
    content_height -= (content.outerHeight() - content.height());
    content.height(content_height);
	if(character.initiated){
		character.resize();
		character.show();
		energyBar.resize();
	}

};

var game = {
	init : function(){
		this.playing = false;
		this.actions = [];
		this.wrong = false;
		this.round =2;
		this.count_act=0;
		this.started = false;
		this.score = 0;
		$('.score').html(this.score);
		this.starting=null;
		this.gen=null;
		this.biginning=null;
	},
	start : function(){
		if (!this.started) {
			//code
			this.started=true;
			var i=3;
			$('#start > span').hide();
			$('#start').css('background','url(images/No'+i+'.png) no-repeat');
			$('#start').css({"background-size":"contain","background-position":"center center"});
			sounds.start[i--].play();
			if (this.starting==null) {
				this.starting = setInterval(function(){
					if (i>=0){
						$('#start').css('background','url(images/No'+(i)+'.png) no-repeat');
					$('#start').css({"background-size":"contain","background-position":"center center"});
					sounds.start[i--].play();
					var str = $('#start').css('background');
					if(str.search("No0.png") != -1){
						game.biginning = setTimeout(function(){
							$('#start').hide();
							energyBar.run();
							game.random();
							//alert(pro+" new");
							clearInterval(game.starting);
							game.starting=null;
							game.beginning = null;
						},700);
					}
					}
				},700);
			}
		}
	},
	touch : function(val){
		console.log(this.count_act);
		if(this.playing){
			if(val!=this.actions[this.count_act++]){
				character.pc_idx = 5;
				this.wrong=true;
				$('#right').css('background-color','#ff3354');
				navigator.notification.vibrate(500);
			}else{
				this.score += 50;
				character.pc_idx = val;
			}
			//sounds.skip();
			$('.score').html(this.score);
			sounds.effect[character.pc_idx].stop();
			sounds.effect[character.pc_idx].play();
			character.drawPC();
		}
	},
	release : function(){
		if(this.playing){
			if(this.wrong){
				this.wrong=false;
				this.playing=false;
				this.fail=setTimeout(function(){
					$("#right").css("background-color","#fff45c");
					character.pc_idx = 0;
					character.drawPC();
					game.random();
				},500);
				if(this.round>2){
					this.round--;
				}
				//setTimeout(rand_act,300);
			}else {
				character.pc_idx = 0;
				character.drawPC();
				if(this.count_act==this.round){
					this.playing=false;
					energyBar.energy += this.round;
					this.score += this.round*100;
					$('.score').html(this.score);
					sounds.nice.play();
					$('#right').css('background-color','#97fd6f');
					if(this.round!=10){
						this.round++;
					}
					this.success=setTimeout(function(){
						$("#right").css("background-color","#fff45c");
						game.random();
					},300);
					//setTimeout(rand_act,300);
				}
			}
		}
	},
	random : function(){
		for(i=0;i<this.round;i++){
			this.actions[i]=Math.floor(Math.random()*4+1);
		}
		this.count_act=0;
		if(this.gen==null){
		    this.gen = setInterval(function(){
			character.npc_idx = game.actions[game.count_act++];
			sounds.effect[character.npc_idx].stop();
			sounds.effect[character.npc_idx].play();
			character.drawNPC()
			if((game.count_act==game.round) && game.count_act!=0){
			    clearInterval(game.gen);
			    game.gen=null;
			    game.playing=true;
			    game.count_act=0;
			}
		    },600);
		} 
	},
	reset : function(){
		$('#start').show();
		$('#start > span').show();
		$('#start').css('background','none');
		$('#start').css('background-color','black');
		//alert(pro+"clear");
		this.started=false;
		energyBar.reset();
		character.reset();
		allStop();
	}
};

function allStop() {
	if(game.gen!=null){
	    clearInterval(game.gen);
	    game.gen=null;
		game.count_act=0;
	}
	if (game.starting!=null) {
		clearInterval(game.starting);
	}
	clearTimeout(game.success);
	clearTimeout(game.fail);
	if (game.beginning!=null) {
		clearTimeout(game.beginning);
	}
	energyBar.cancel();
}

var character = {
	init : function (){
		this.initiated=true;
		this.pc_idx = 0;
		this.npc_idx = 0;
		
		$("#right").css("background-color","#fff45c");
		//$('#progressBar').width($('#energy').width()/2);
		this.can_pc = document.getElementById("canvas_pc");
		this.can_npc = document.getElementById("canvas_npc");
		
		if(!this.can_pc || !this.can_pc.getContext || !this.can_npc || !this.can_npc.getContext)
			alert("Canvas doesn't exist");
		this.context_pc = this.can_pc.getContext("2d");
		this.context_npc = this.can_npc.getContext("2d");
		
		this.resize();
		
		this.image_arrow = new Image();
		this.image_arrow.src = "images/arrow.png";
		this.image_pc = new Image();
		this.image_pc.src = "images/pc.png";
		this.image_pc.addEventListener('load', function(){character.drawPC()}, false);
		this.image_npc = new Image();
		this.image_npc.src = "images/npc.png";
		this.image_npc.addEventListener('load', function(){character.drawNPC()}, false);
		

	},
	drawPC : function(){
		var spriteY = this.pc_idx * 310;
		//this.context_pc.fillStyle = "#fff45c";
		//this.context_pc.fillRect(this.char_x, this.char_y, this.char_width, this.char_height);
		this.context_pc.clearRect(0,0,this.can_pc.width,this.can_pc.height);
		this.context_pc.drawImage(this.image_pc, 0, spriteY, 200, 300, this.char_x, this.char_y, parseInt(this.char_width), parseInt(this.char_height));
		if(this.pc_idx!=0){
			var arrowY = (this.pc_idx - 1) * 90;
			this.context_pc.drawImage(this.image_arrow, 0, arrowY, 80, 80, this.arrow_x, this.arrow_y, parseInt(this.arrow_size), parseInt(this.arrow_size));
		}
	},

	drawNPC : function(){
		var spriteY = this.npc_idx * 310;
		//this.context_npc.fillStyle = "#97fd6f";
		//this.context_npc.fillRect(this.char_x, this.char_y, this.char_width, this.char_height);
		this.context_npc.clearRect(0,0,this.can_npc.width,this.can_npc.height);
		this.context_npc.drawImage(this.image_npc, 0, spriteY, 200, 300, this.char_x, this.char_y, parseInt(this.char_width), parseInt(this.char_height));
		if(this.npc_idx!=0){
			var arrowY = (this.npc_idx - 1) * 90;
			this.context_npc.drawImage(this.image_arrow, 0, arrowY, 80, 80, this.arrow_x, this.arrow_y, parseInt(this.arrow_size), parseInt(this.arrow_size));
			setTimeout(function(){character.npc_idx = 0;character.drawNPC();},300);
		}
	},
	resize : function (){
		var content = $(".content:visible");
		this.can_pc.height = content.height() * 0.95;
		this.can_pc.width = content.width()/2;
		
		this.can_npc.height = this.can_pc.height;
		this.can_npc.width = this.can_pc.width;
		
		this.arrow_size = this.can_npc.height / 10;
		this.arrow_x = Math.floor(this.can_pc.width/2)- this.arrow_size/2;
		this.arrow_y = this.arrow_size;

		if(content.height() <=content.width())
			this.char_width = Math.floor(this.can_pc.width*0.4);
		else
			this.char_width = Math.floor(this.can_pc.width*0.8);
		this.char_height = Math.floor((this.char_width/2)*3);
		this.char_x = Math.floor(this.can_pc.width/2)- this.char_width/2;
		this.char_y = Math.floor(this.can_pc.height/2) - this.char_height/2;
	},
	show : function(){
		this.drawPC();
		this.drawNPC();
	},
	reset : function(){
		this.pc_idx = 0;
		this.npc_idx = 0;
	}
};

var energyBar = {
	init : function(){
		this.outer = $('#progressBar');
		this.inner = $('#progressBar > div');
		this.bar = $('#energy');
		this.reset();
	},
	resize : function(){
		this.outer.width(this.bar.width()/2);
		this.show();
	},
	show : function(){
		this.energybar = this.energy * this.outer.width() / 100;
		this.inner.css('width',this.energybar+'px');
	},
	check_over : function(){
		if (this.inner.width()<=0){
			sounds.timeup.play();
			this.cancel();
			setTimeout('$.mobile.changePage( "#gameover", { transition: "fade", changeHash: true })',1000);
			//$.mobile.changePage( "#gameover", { transition: "flip", changeHash: true });
		}
	},
	run : function(){
		if(this.running==null){
			this.running = setInterval(function(){
				console.log('run');
				energyBar.energy--;
				energyBar.show();
				energyBar.check_over();
			},500);
		}else{
			//this.cancel();
			game.reset();
		}

	},
	cancel : function(){
        if(this.running!=null){
            clearInterval(this.running);
            this.running = null;
        }
		this.show();
	},
	reset : function(){
		this.energy=100;
		this.cancel();
	}
};