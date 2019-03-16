$(document).ready(function(){
    $('.menuToggle').click(function(){
        $('.container').toggleClass('showMenu');
        $('.menuToggle').toggleClass('active');
    });

    $('.navigationLinks').click(function(){
        $('.container').toggleClass('showMenu');
        $('.menuToggle').toggleClass('active');
    })

    setTimeout(function(){
      $('.menuToggle').toggleClass('animateToggle');
    }, 5000);

    setTimeout(function(){
      $('.menuToggle').toggleClass('animateToggle');
    }, 5500);

    setTimeout(function(){
      $('.menuToggle').toggleClass('animateToggle');
    }, 6000);

    setTimeout(function(){
      $('.menuToggle').toggleClass('animateToggle');
    }, 6500);
});
