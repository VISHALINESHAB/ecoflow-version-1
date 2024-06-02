// script.js
/* JavaScript to trigger the background transition and material transformation animation */

document.addEventListener('DOMContentLoaded', (event) => {
    const section = document.getElementById('reuse-recycle-reduce');
    const materialItems = section.querySelectorAll('.material-item');

    // Trigger background transition when scrolling to the section
    window.addEventListener('scroll', () => {
        const sectionTop = section.getBoundingClientRect().top;
        const windowHeight = window.innerHeight;

        if (sectionTop < windowHeight / 2) {
            section.style.background = 'url("green.png") no-repeat center center fixed';
            section.style.backgroundSize = 'cover';
        }
    });

    // Trigger material transformation animation when scrolling to each material item
    window.addEventListener('scroll', () => {
        materialItems.forEach(item => {
            const itemTop = item.getBoundingClientRect().top;
            const windowHeight = window.innerHeight;

            if (itemTop < windowHeight * 0.8) {
                item.classList.add('material-transform');
            }
        });
    });
});


document.addEventListener('DOMContentLoaded', (event) => {
    // Animate the buttons on hover
    const buttons = document.querySelectorAll('.btn-custom');
    buttons.forEach(button => {
        button.addEventListener('mouseover', () => {
            button.style.transform = 'scale(1.1)';
        });
        button.addEventListener('mouseout', () => {
            button.style.transform = 'scale(1)';
        });
    });

    // Scroll animations for sections
    const sections = document.querySelectorAll('.section, .card');
    const options = {
        threshold: 0.1
    };

    const observer = new IntersectionObserver((entries, observer) => {
        entries.forEach(entry => {
            if (entry.isIntersecting) {
                entry.target.classList.add('animate');
                observer.unobserve(entry.target);
            }
        });
    }, options);

    sections.forEach(section => {
        observer.observe(section);
    });
});

// Function to smooth scroll to the top
document.querySelector('.navbar-brand').addEventListener('click', () => {
    window.scrollTo({
        top: 0,
        behavior: 'smooth'
    });
});
document.addEventListener('DOMContentLoaded', (event) => {
    // Your existing script

    // Add this part for the navbar scroll effect
    const navbar = document.querySelector('.navbar');
    window.addEventListener('scroll', () => {
        if (window.scrollY > 50) { // Adjust this value based on when you want the change to occur
            navbar.classList.add('scrolled');
        } else {
            navbar.classList.remove('scrolled');
        }
    });
});